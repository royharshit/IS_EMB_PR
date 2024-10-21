# Define the repository URL and branch
REPO_URL = https://github.com/royharshit/b1_instruction.git
BRANCH = stable

# Default target to clone the repository
.PHONY: clone
clone:
	git clone $(REPO_URL) -b $(BRANCH)

# Optional target to clean up the cloned directory
.PHONY: clean
clean:
	rm -rf b1_instruction

