#!/usr/bin/env bash

# this should be called from a git hook in the child repos, with a path to the child repo as argument

errexit() {
    echo "$@" >&2
    exit 1
}

# sanity check that we're executing in the zmk-stuff repo
git remote get-url origin 2>/dev/null | grep -q 'zmk-stuff' || errexit "This script must be run from within the zmk-stuff repository, but git remote was $(git remote get-url origin 2>/dev/null), not zmk-stuff."

# sanity check that (exactly one) child path argument is provided...
[ $# -eq 1 ] || errexit "No child path argument provided."
child_path="$1"

# ... and that it exists...
[ -d "$child_path" ] || errexit "Provided child path argument '$1' is not a directory."
child_path_relative=$(realpath --relative-to="$(pwd)" "$child_path")

# (one more sanity check: should be equivalent to basename)
[ "$(basename $child_path)" = "$child_path_relative" ] || errexit "Provided child path argument '$1' could not be resolved."

# ... and that it is a git submodule
git config --file .gitmodules --get-regexp path | grep -q "$child_path_relative$" || errexit "Provided child path argument '$1' is not a git submodule."


# sanity check that there are submodule changes to commit
git status --short | grep -q "$child_path_relative" || errexit "No changes to commit in $child_path_relative submodule."

# verify nothing else is staged here (parent), otherwise abort
git diff --quiet --cached || errexit "There are staged changes in the parent repository. Please commit or unstage them before pushing."

# verify there are no unpushed commits here (parent), otherwise abort
[ "$(git rev-list --count @{u}..HEAD)" -eq 0 ] || errexit "There are unpushed commits in the parent repository. Please push them before pushing this repository."
#
# if there are UNTRACKED changes (?? in short porcelain) in the parent repo, abort
git status --ignore-submodules --short --untracked=all | grep -q '??' && errexit "There are untracked files in the parent repository. Please commit or remove them before pushing."

# if there are changes in the parent repo *other than submodule changes*, commit them automatically for the user
git status --ignore-submodules --short --untracked=no | grep -q ' ' && {
    # give the user 3 seconds to abort
    for i in 3 2 1; do
        echo -e "There are changes in the parent repository. \e[31mCommitting\e[0m them automatically in \e[31m$i...\e[0m Press Ctrl-C to abort."
        sleep 1
    done
    git commit -a -m "Auto-commit known changes before pushing submodule"
}

git commit "$child_path" -m "Update $child_path_relative submodule to latest"
git push

