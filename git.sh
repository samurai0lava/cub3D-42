#!/bin/bash

# Check if branch and commit message are provided
if [ $# -lt 2 ]; then
    echo "Error: Please provide both branch name and commit message"
    echo "Usage: $0 <branch_name> \"your commit message\""
    exit 1
fi

# Store the branch name and commit message
BRANCH_NAME="$1"
COMMIT_MESSAGE="$2"

# Check if branch exists
if ! git show-ref --verify --quiet "refs/heads/$BRANCH_NAME"; then
    echo "Error: Branch '$BRANCH_NAME' does not exist"
    exit 1
fi

# Switch to specified branch
echo "Switching to branch: $BRANCH_NAME"
git checkout "$BRANCH_NAME"
if [ $? -ne 0 ]; then
    echo "Error: Failed to switch to branch '$BRANCH_NAME'"
    exit 1
fi

# Check if there are any changes to commit
if [ -z "$(git status --porcelain)" ]; then
    echo "No changes to commit"
    exit 0
fi

# Fetch latest changes
echo "Fetching latest changes..."
git fetch

# Check if we need to pull
UPSTREAM="origin/$BRANCH_NAME"
LOCAL=$(git rev-parse @)
REMOTE=$(git rev-parse "$UPSTREAM" 2>/dev/null) || REMOTE=$LOCAL
BASE=$(git merge-base @ "$UPSTREAM" 2>/dev/null) || BASE=$LOCAL

if [ $REMOTE = $BASE ]; then
    echo "No pull needed. Branch is up to date."
elif [ $LOCAL = $REMOTE ]; then
    echo "No pull needed. Branch is up to date."
else
    echo "Remote changes detected. Pulling latest changes..."
    git pull origin "$BRANCH_NAME"
    
    # Check if pull was successful
    if [ $? -ne 0 ]; then
        echo "Error: Pull failed. Please resolve conflicts manually."
        exit 1
    fi
fi

# Add all changes
echo "Adding changes..."
git add .

# Commit with message
echo "Committing changes..."
git commit -m "$COMMIT_MESSAGE"

if [ $? -eq 0 ]; then
    echo "Successfully committed changes to branch: $BRANCH_NAME"
    echo "You can now push your changes with: git push origin $BRANCH_NAME"
else
    echo "Error: Commit failed"
    exit 1
fi