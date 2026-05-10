To configure everything so that pushes work correctly and the GH action runs with updated content:

1. Checkout this repo
2. Initialize the git submodules, and then set them to their respective default branches
3. Configure the included hook for each submodule: `for dir in zmk-*; do cd $dir; git config core.hooksPath ../.githooks; cd ..; done`

-> This should ensure that any changes in the parent repo get auto-committed and pushed when a submodule is pushed, so that the GH action always builds everything with the most up-to-date shared state

TODO:
- [ ] Make sure that submodule updates are not manually committed in the parent repo, so that the child repos dont fail when pushing their updates and wanting to commit & push that update in the parent. 
    - basically a git commit pre-hook in the parent
