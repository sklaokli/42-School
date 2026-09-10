# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/05 15:11:14 by sklaokli          #+#    #+#              #
#    Updated: 2026/09/11 03:41:27 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Defaults
BRANCH      ?= master
MAIN_BRANCH ?= main
REMOTE      ?= origin
DIR         ?=

# ANSI Colors
CYAN   := \033[36m
GREEN  := \033[32m
YELLOW := \033[33m
RED    := \033[31m
RESET  := \033[0m
BOLD   := \033[1m

.PHONY: all help push pull status remotes backup subpush subpull \
        push-libft push-printf push-gnl push-minitalk \
        push-pushswap push-solong push-minishell push-philo push-minirt \
        push-webserv clean-all fclean-all norm test test-libft \
        setup-hooks submit sanitize valgrind


all: help

help:
	@echo "$(BOLD)$(CYAN)=== 42-School Monorepo Management Console ===$(RESET)"
	@echo ""
	@echo "$(BOLD)Monorepo Git Operations:$(RESET)"
	@echo "  $(GREEN)make push$(RESET)                   Push entire monorepo to GitHub ($(REMOTE)/$(MAIN_BRANCH))"
	@echo "  $(GREEN)make pull$(RESET)                   Pull latest changes for monorepo"
	@echo "  $(GREEN)make status$(RESET) (or $(GREEN)make st$(RESET))    Show repository working status"
	@echo "  $(GREEN)make remotes$(RESET)                List all configured remotes with URLs"
	@echo "  $(GREEN)make backup$(RESET)                 Create a timestamped backup of the .git directory"
	@echo ""
	@echo "$(BOLD)Quality & 42 Intra Submission Tooling:$(RESET)"
	@echo "  $(GREEN)make setup-hooks$(RESET)            Install Git hooks (Norminette, commit-msg, artifact guards)"
	@echo "  $(GREEN)make submit PROJECT=<name> [REMOTE=<remote_or_url>] [BRANCH=master]$(RESET)"
	@echo "      Automated Norm check, test execution, fclean, and subtree push to 42 Intra"
	@echo "      $(YELLOW)Example:$(RESET) make submit PROJECT=push_swap REMOTE=git@vogsphere.42bangkok.com:..."
	@echo ""
	@echo "$(BOLD)Subtree Operations (Push/Pull Single Project):$(RESET)"
	@echo "  $(GREEN)make subpush DIR=<path> REMOTE=<remote> [BRANCH=master]$(RESET)"
	@echo "      Push a single project folder to an external repository"
	@echo "      $(YELLOW)Example:$(RESET) make subpush DIR=r02/so_long REMOTE=vogsphere-solong"
	@echo "  $(GREEN)make subpull DIR=<path> REMOTE=<remote> [BRANCH=master]$(RESET)"
	@echo "      Pull updates for a single project folder from an external repository"
	@echo "      $(YELLOW)Example:$(RESET) make subpull DIR=r02/so_long REMOTE=vogsphere-solong"
	@echo ""
	@echo "$(BOLD)Project Quick-Push Shortcuts:$(RESET)"
	@echo "  $(GREEN)make push-libft REMOTE=<remote>$(RESET)      Push r00/libft"
	@echo "  $(GREEN)make push-printf REMOTE=<remote>$(RESET)     Push r01/ft_printf"
	@echo "  $(GREEN)make push-gnl REMOTE=<remote>$(RESET)        Push r01/get_next_line"
	@echo "  $(GREEN)make push-minitalk REMOTE=<remote>$(RESET)   Push r02/minitalk"
	@echo "  $(GREEN)make push-pushswap REMOTE=<remote>$(RESET)   Push r02/push_swap"
	@echo "  $(GREEN)make push-solong REMOTE=<remote>$(RESET)     Push r02/so_long"
	@echo "  $(GREEN)make push-minishell REMOTE=<remote>$(RESET)  Push r03/minishell"
	@echo "  $(GREEN)make push-philo REMOTE=<remote>$(RESET)      Push r03/philosophers"
	@echo "  $(GREEN)make push-minirt REMOTE=<remote>$(RESET)     Push r04/miniRT"
	@echo "  $(GREEN)make push-webserv REMOTE=<remote>$(RESET)    Push r05/webserv"
	@echo ""
	@echo "$(BOLD)Workspace Maintenance & Testing:$(RESET)"
	@echo "  $(GREEN)make test PROJECT=<name>$(RESET)    Run tests for a project (e.g. PROJECT=libft)"
	@echo "  $(GREEN)make test-libft$(RESET)             Run unit tests for r00/libft"
	@echo "  $(GREEN)make sanitize PROJECT=<name>$(RESET)        Compile & run tests with AddressSanitizer (ASan/UBSan)"
	@echo "  $(GREEN)make valgrind PROJECT=<name> [BIN=<name>] [ARGS='...']$(RESET)"
	@echo "      Run Valgrind leak detection on project test runner or executable"
	@echo "  $(GREEN)make clean-all$(RESET)              Run clean in all subprojects"
	@echo "  $(GREEN)make fclean-all$(RESET)             Run fclean in all subprojects"
	@echo "  $(GREEN)make norm [DIR=...]$(RESET)          Run Norminette across projects"

# --- Monorepo Git Operations ---

push:
	@echo "$(YELLOW)Pushing monorepo to $(REMOTE)/$(MAIN_BRANCH)...$(RESET)"
	git push $(REMOTE) $(MAIN_BRANCH)

pull:
	@echo "$(YELLOW)Pulling latest changes from $(REMOTE)/$(MAIN_BRANCH)...$(RESET)"
	git pull $(REMOTE) $(MAIN_BRANCH)

status st:
	@git status

remotes:
	@echo "$(CYAN)Configured Git Remotes:$(RESET)"
	@git remote -v

backup:
	@mkdir -p backups
	@tar -czf backups/git_backup_$$(date +%Y%m%d_%H%M%S).tar.gz .git
	@echo "$(GREEN)Monorepo .git backup saved to backups/$(RESET)"

# --- Subtree Operations ---

subpush:
	@if [ -z "$(DIR)" ] || [ -z "$(REMOTE)" ]; then \
		echo "$(RED)Error: Please specify both DIR and REMOTE.$(RESET)"; \
		echo "Usage: make subpush DIR=r02/so_long REMOTE=<remote-name> [BRANCH=master]"; \
		exit 1; \
	fi
	@if [ ! -d "$(DIR)" ]; then \
		echo "$(RED)Error: Directory '$(DIR)' not found.$(RESET)"; \
		exit 1; \
	fi
	@echo "$(YELLOW)Pushing $(DIR) to $(REMOTE)/$(BRANCH)...$(RESET)"
	git subtree push --prefix=$(DIR) $(REMOTE) $(BRANCH)

subpull:
	@if [ -z "$(DIR)" ] || [ -z "$(REMOTE)" ]; then \
		echo "$(RED)Error: Please specify both DIR and REMOTE.$(RESET)"; \
		echo "Usage: make subpull DIR=r02/so_long REMOTE=<remote-name> [BRANCH=master]"; \
		exit 1; \
	fi
	@if [ ! -d "$(DIR)" ]; then \
		echo "$(RED)Error: Directory '$(DIR)' not found.$(RESET)"; \
		exit 1; \
	fi
	@echo "$(YELLOW)Pulling $(DIR) from $(REMOTE)/$(BRANCH)...$(RESET)"
	git subtree pull --prefix=$(DIR) $(REMOTE) $(BRANCH) --squash

# --- Subtree Project Shortcuts ---

push-libft:
	@$(MAKE) subpush DIR=r00/libft REMOTE=$(REMOTE) BRANCH=$(BRANCH)

push-printf:
	@$(MAKE) subpush DIR=r01/ft_printf REMOTE=$(REMOTE) BRANCH=$(BRANCH)

push-gnl:
	@$(MAKE) subpush DIR=r01/get_next_line REMOTE=$(REMOTE) BRANCH=$(BRANCH)

push-minitalk:
	@$(MAKE) subpush DIR=r02/minitalk REMOTE=$(REMOTE) BRANCH=$(BRANCH)

push-pushswap:
	@$(MAKE) subpush DIR=r02/push_swap REMOTE=$(REMOTE) BRANCH=$(BRANCH)

push-solong:
	@$(MAKE) subpush DIR=r02/so_long REMOTE=$(REMOTE) BRANCH=$(BRANCH)

push-minishell:
	@$(MAKE) subpush DIR=r03/minishell REMOTE=$(REMOTE) BRANCH=$(BRANCH)

push-philo:
	@$(MAKE) subpush DIR=r03/philosophers REMOTE=$(REMOTE) BRANCH=$(BRANCH)

push-minirt:
	@$(MAKE) subpush DIR=r04/miniRT REMOTE=$(REMOTE) BRANCH=$(BRANCH)

push-webserv:
	@$(MAKE) subpush DIR=r05/webserv REMOTE=$(REMOTE) BRANCH=$(BRANCH)

# --- Workspace Maintenance ---

clean-all:
	@echo "$(YELLOW)Cleaning object files across all subprojects...$(RESET)"
	@find r* -name "Makefile" -not -path "*/.*/*" | while read -r mf; do \
		dir=$$(dirname "$$mf"); \
		if grep -q "^clean:" "$$mf" 2>/dev/null; then \
			$(MAKE) -C "$$dir" clean --no-print-directory 2>/dev/null || true; \
		fi; \
	done
	@echo "$(GREEN)Done cleaning.$(RESET)"

fclean-all:
	@echo "$(YELLOW)Fully cleaning (fclean) across all subprojects...$(RESET)"
	@find r* -name "Makefile" -not -path "*/.*/*" | while read -r mf; do \
		dir=$$(dirname "$$mf"); \
		if grep -q "^fclean:" "$$mf" 2>/dev/null; then \
			$(MAKE) -C "$$dir" fclean --no-print-directory 2>/dev/null || true; \
		elif grep -q "^clean:" "$$mf" 2>/dev/null; then \
			$(MAKE) -C "$$dir" clean --no-print-directory 2>/dev/null || true; \
		fi; \
	done
	@echo "$(GREEN)Done fcleaning all build artifacts.$(RESET)"

norm norminette:
	@if [ -n "$(DIR)" ]; then \
		echo "$(YELLOW)Running norminette on $(DIR) (excluding tests/)...$(RESET)"; \
		find $(DIR) -type f \( -name "*.c" -o -name "*.h" \) | grep -v -E '(^|/)tests?/' | xargs -r norminette; \
	else \
		echo "$(YELLOW)Running norminette on all C projects (excluding tests/)...$(RESET)"; \
		find r00/ r01/ r02/ r03/ r04/miniRT -type f \( -name "*.c" -o -name "*.h" \) 2>/dev/null | grep -v -E '(^|/)tests?/' | xargs -r norminette; \
	fi

test-libft:
	@$(MAKE) -C r00/libft test

test:
	@if [ -z "$(PROJECT)" ]; then \
		echo "$(RED)Error: Please specify PROJECT (e.g. make test PROJECT=libft)$(RESET)"; \
		exit 1; \
	fi
	@if [ "$(PROJECT)" = "libft" ]; then \
		$(MAKE) -C r00/libft test; \
	else \
		found=0; \
		for d in $$(find r* -maxdepth 2 -name "$(PROJECT)" -type d); do \
			found=1; \
			$(MAKE) -C "$$d" test; \
		done; \
		if [ $$found -eq 0 ]; then \
			echo "$(RED)Error: Project '$(PROJECT)' not found.$(RESET)"; \
			exit 1; \
		fi; \
	fi

# --- Quality & 42 Intra Submission Automation ---

setup-hooks:
	@echo "$(CYAN)Configuring Git hooks directory...$(RESET)"
	@git config core.hooksPath .githooks
	@chmod +x .githooks/pre-commit
	@chmod +x .githooks/commit-msg
	@echo "$(GREEN)$(BOLD)✓ Git hooks installed successfully!$(RESET)"
	@echo "  $(CYAN)• pre-commit:$(RESET) Auto-verifies Norminette on staged files & blocks *.o/binary artifacts."
	@echo "  $(CYAN)• commit-msg:$(RESET) Enforces Conventional Commits standard (feat, fix, test, refactor, etc.)."

submit:
	@if [ -z "$(PROJECT)" ]; then \
		echo "$(RED)$(BOLD)Error: PROJECT is required.$(RESET)"; \
		echo "Usage: make submit PROJECT=<project-name> REMOTE=<remote-name-or-url> [BRANCH=master]"; \
		echo "  $(YELLOW)Example:$(RESET) make submit PROJECT=libft REMOTE=git@vogsphere.42bangkok.com:vogsphere/intra-..."; \
		exit 1; \
	fi
	@PROJECT_DIR=$$(find r* -maxdepth 2 -name "$(PROJECT)" -type d | head -n 1); \
	if [ -z "$$PROJECT_DIR" ] || [ ! -d "$$PROJECT_DIR" ]; then \
		echo "$(RED)Error: Could not locate directory for project '$(PROJECT)'.$(RESET)"; \
		exit 1; \
	fi; \
	REMOTE_TARGET="$(REMOTE)"; \
	if [ -z "$$REMOTE_TARGET" ] || [ "$$REMOTE_TARGET" = "origin" ]; then \
		if git remote | grep -q "^vogsphere-$(PROJECT)$$"; then \
			REMOTE_TARGET="vogsphere-$(PROJECT)"; \
		elif git remote | grep -q "^vogsphere$$"; then \
			REMOTE_TARGET="vogsphere"; \
		else \
			echo "$(RED)$(BOLD)Error: 42 submission remote not specified.$(RESET)"; \
			echo "Please provide REMOTE=<url-or-name>."; \
			echo "  $(YELLOW)Example:$(RESET) make submit PROJECT=$(PROJECT) REMOTE=git@vogsphere.42bangkok.com:vogsphere/intra-..."; \
			exit 1; \
		fi; \
	fi; \
	if echo "$$REMOTE_TARGET" | grep -E '^git@|^https?://'; then \
		REMOTE_NAME="vogsphere-$(PROJECT)"; \
		if git remote | grep -q "^$$REMOTE_NAME$$"; then \
			git remote set-url "$$REMOTE_NAME" "$$REMOTE_TARGET"; \
		else \
			git remote add "$$REMOTE_NAME" "$$REMOTE_TARGET"; \
		fi; \
		REMOTE_TARGET="$$REMOTE_NAME"; \
		echo "$(CYAN)Configured remote '$$REMOTE_NAME'.$(RESET)"; \
	fi; \
	echo ""; \
	echo "$(BOLD)$(CYAN)=========================================$(RESET)"; \
	echo "$(BOLD)$(CYAN)     42 INTRA SUBMISSION PIPELINE        $(RESET)"; \
	echo "$(BOLD)$(CYAN)=========================================$(RESET)"; \
	echo "$(CYAN)Target Project :$(RESET) $(BOLD)$$PROJECT_DIR$(RESET)"; \
	echo "$(CYAN)Intra Remote   :$(RESET) $(BOLD)$$REMOTE_TARGET ($(BRANCH))$(RESET)"; \
	echo ""; \
	echo "$(BOLD)[Step 1/4] Running 42 Norminette Quality Gate...$(RESET)"; \
	if command -v norminette >/dev/null 2>&1; then \
		NORM_FILES=$$(find "$$PROJECT_DIR" -type f \( -name "*.c" -o -name "*.h" \) | grep -v -E '(^|/)tests?/' || true); \
		if [ -n "$$NORM_FILES" ]; then \
			norminette $$NORM_FILES || { echo "$(RED)$(BOLD)❌ Submission Aborted: Norminette errors found in $$PROJECT_DIR!$(RESET)"; exit 1; }; \
			echo "$(GREEN)✓ Norminette passed with 0 errors.$(RESET)"; \
		else \
			echo "$(YELLOW)No C/H files found to check.$(RESET)"; \
		fi; \
	else \
		echo "$(YELLOW)Warning: Norminette not installed. Skipping local norm check.$(RESET)"; \
	fi; \
	echo ""; \
	echo "$(BOLD)[Step 2/4] Running Automated Project Tests...$(RESET)"; \
	if [ -f "$$PROJECT_DIR/Makefile" ] && grep -q "^test:" "$$PROJECT_DIR/Makefile" 2>/dev/null; then \
		$(MAKE) -C "$$PROJECT_DIR" test || { echo "$(RED)$(BOLD)❌ Submission Aborted: Tests failed in $$PROJECT_DIR!$(RESET)"; exit 1; }; \
		echo "$(GREEN)✓ All tests passed successfully.$(RESET)"; \
	else \
		echo "$(YELLOW)No test suite found in $$PROJECT_DIR. Continuing.$(RESET)"; \
	fi; \
	echo ""; \
	echo "$(BOLD)[Step 3/4] Cleaning Build Objects (fclean)...$(RESET)"; \
	if [ -f "$$PROJECT_DIR/Makefile" ]; then \
		if grep -q "^fclean:" "$$PROJECT_DIR/Makefile" 2>/dev/null; then \
			$(MAKE) -C "$$PROJECT_DIR" fclean --no-print-directory || true; \
		elif grep -q "^clean:" "$$PROJECT_DIR/Makefile" 2>/dev/null; then \
			$(MAKE) -C "$$PROJECT_DIR" clean --no-print-directory || true; \
		fi; \
		echo "$(GREEN)✓ Cleaned build objects.$(RESET)"; \
	fi; \
	echo ""; \
	echo "$(BOLD)[Step 4/4] Pushing Clean Subtree to 42 Intra...$(RESET)"; \
	echo "$(YELLOW)Executing: git subtree push --prefix=$$PROJECT_DIR $$REMOTE_TARGET $(BRANCH)$(RESET)"; \
	git subtree push --prefix="$$PROJECT_DIR" "$$REMOTE_TARGET" "$(BRANCH)" && \
	echo "$(GREEN)$(BOLD)🎉 Successfully submitted $(PROJECT) to 42 Intra ($$REMOTE_TARGET/$(BRANCH))!$(RESET)"

sanitize:
	@if [ -z "$(PROJECT)" ]; then \
		echo "$(RED)$(BOLD)Error: PROJECT is required.$(RESET)"; \
		echo "Usage: make sanitize PROJECT=<project-name>"; \
		echo "  $(YELLOW)Example:$(RESET) make sanitize PROJECT=libft"; \
		exit 1; \
	fi
	@PROJECT_DIR=$$(find r* -maxdepth 2 -name "$(PROJECT)" -type d | head -n 1); \
	if [ -z "$$PROJECT_DIR" ] || [ ! -d "$$PROJECT_DIR" ]; then \
		echo "$(RED)Error: Project '$(PROJECT)' not found in r00-r05.$(RESET)"; \
		exit 1; \
	fi; \
	echo "$(CYAN)$(BOLD)[AddressSanitizer] Compiling and testing $$PROJECT_DIR with ASan & UBSan...$(RESET)"; \
	SAN_FLAGS="-Wall -Wextra -Werror -g3 -fsanitize=address,undefined"; \
	SAN_CXXFLAGS="-Wall -Wextra -Werror -std=c++98 -g3 -fsanitize=address,undefined"; \
	if grep -q "^test:" "$$PROJECT_DIR/Makefile" 2>/dev/null; then \
		$(MAKE) -C "$$PROJECT_DIR" re test CFLAGS="$$SAN_FLAGS" CXXFLAGS="$$SAN_CXXFLAGS" || { echo "$(RED)❌ Sanitizer test failed in $$PROJECT_DIR$(RESET)"; exit 1; }; \
		$(MAKE) -C "$$PROJECT_DIR" fclean --no-print-directory || true; \
		echo "$(GREEN)$(BOLD)✓ All tests completed with AddressSanitizer and UndefinedBehaviorSanitizer!$(RESET)"; \
	else \
		$(MAKE) -C "$$PROJECT_DIR" re CFLAGS="$$SAN_FLAGS" CXXFLAGS="$$SAN_CXXFLAGS" || { echo "$(RED)❌ Build failed in $$PROJECT_DIR$(RESET)"; exit 1; }; \
		echo "$(GREEN)$(BOLD)✓ Project compiled with AddressSanitizer flags successfully.$(RESET)"; \
	fi

valgrind:
	@if [ -z "$(PROJECT)" ]; then \
		echo "$(RED)$(BOLD)Error: PROJECT is required.$(RESET)"; \
		echo "Usage: make valgrind PROJECT=<project-name> [BIN=<binary>] [ARGS=\"...\"]"; \
		echo "  $(YELLOW)Example:$(RESET) make valgrind PROJECT=libft"; \
		echo "  $(YELLOW)Example:$(RESET) make valgrind PROJECT=so_long BIN=so_long ARGS=\"maps/valid/map.ber\""; \
		exit 1; \
	fi
	@if ! command -v valgrind >/dev/null 2>&1; then \
		echo "$(RED)$(BOLD)Error: valgrind is not installed or not in PATH.$(RESET)"; \
		exit 1; \
	fi
	@PROJECT_DIR=$$(find r* -maxdepth 2 -name "$(PROJECT)" -type d | head -n 1); \
	if [ -z "$$PROJECT_DIR" ] || [ ! -d "$$PROJECT_DIR" ]; then \
		echo "$(RED)Error: Project '$(PROJECT)' not found in r00-r05.$(RESET)"; \
		exit 1; \
	fi; \
	VALGRIND_CMD="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1"; \
	if [ -n "$(BIN)" ]; then \
		TARGET_BIN="$$PROJECT_DIR/$(BIN)"; \
		echo "$(YELLOW)Rebuilding $$PROJECT_DIR with debug symbols (-g3) for Valgrind...$(RESET)"; \
		$(MAKE) -C "$$PROJECT_DIR" re CFLAGS="-Wall -Wextra -Werror -g3" CXXFLAGS="-Wall -Wextra -Werror -std=c++98 -g3"; \
		echo "$(CYAN)$(BOLD)[Valgrind] Running leak check on $$TARGET_BIN $(ARGS)...$(RESET)"; \
		$$VALGRIND_CMD "$$TARGET_BIN" $(ARGS); \
		echo "$(GREEN)$(BOLD)✓ Valgrind completed with 0 leaks!$(RESET)"; \
	elif [ "$(PROJECT)" = "libft" ] || [ "$$PROJECT_DIR" = "r00/libft" ]; then \
		echo "$(CYAN)$(BOLD)[Valgrind] Building & running libft test suite under Valgrind...$(RESET)"; \
		$(MAKE) -C r00/libft fclean --no-print-directory; \
		$(MAKE) -C r00/libft bonus CFLAGS="-Wall -Wextra -Werror -g3" --no-print-directory; \
		cc -Wall -Wextra -Werror -g3 r00/libft/tests/testMain.c -L r00/libft -lft -I r00/libft -o r00/libft/testRunner; \
		$$VALGRIND_CMD ./r00/libft/testRunner; \
		rm -f r00/libft/testRunner; \
		$(MAKE) -C r00/libft fclean --no-print-directory; \
		echo "$(GREEN)$(BOLD)✓ Valgrind leak check passed: 0 leaks!$(RESET)"; \
	elif [ -f "$$PROJECT_DIR/Makefile" ] && grep -q "^test:" "$$PROJECT_DIR/Makefile" 2>/dev/null; then \
		echo "$(CYAN)$(BOLD)[Valgrind] Running $$PROJECT_DIR test suite with Valgrind...$(RESET)"; \
		$(MAKE) -C "$$PROJECT_DIR" test VALGRIND="$$VALGRIND_CMD"; \
	else \
		echo "$(YELLOW)Looking for project binary in $$PROJECT_DIR...$(RESET)"; \
		TARGET_BIN=$$(find "$$PROJECT_DIR" -maxdepth 1 -type f -executable ! -name "*.sh" ! -name "*.py" | head -n 1); \
		if [ -n "$$TARGET_BIN" ]; then \
			echo "$(CYAN)[Valgrind] Testing $$TARGET_BIN...$(RESET)"; \
			$$VALGRIND_CMD "$$TARGET_BIN" $(ARGS); \
			echo "$(GREEN)$(BOLD)✓ Valgrind completed with 0 leaks!$(RESET)"; \
		else \
			echo "$(RED)No executable found in $$PROJECT_DIR. Please compile or pass BIN=<name>.$(RESET)"; \
			exit 1; \
		fi; \
	fi
