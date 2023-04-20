# @author    Clément Vidon
# @created   230320 00:00:00  by  clem@spectre
# @modified  230417 10:25:51  by  clem@spectre
# @filename  Makefile

############ PROJECT
####################

NAME        := a.out

LIBS        :=
LIBS_PATH   :=

SRC_DIR     := src
SRCS        := \
	main.cpp \
	Warlock.cpp \

INC_DIR     := include
BUILD_DIR   := .build

LEAKS		:= valgrind -q --leak-check=yes --show-leak-kinds=all
TESTS		:= bash test/tests.sh $(NAME) "$(LEAKS)"

############ GENERIC
####################

## compilation vars
###################

SRCS        := $(SRCS:%=$(SRC_DIR)/%)
INCS        := $(INC_DIR) $(dir $(SRCS))
OBJS        := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CXX         := c++
CXXFLAGS    := -Wall -Wextra -Werror -std=c++98
DEVFLAGS    := -Wconversion -Wsign-conversion -pedantic
DEVFLAGS    += -fno-omit-frame-pointer -Og -D DEV
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_PATH)))
LDLIBS      := $(addprefix -l,$(LIBS))

## utils vars
#############

RM          := rm -f
MAKEFLAGS   := --no-print-directory --jobs -C
DIR_DUP     = mkdir -p $(@D)

FILE_AGE    := $$(date -d@$$(($$(date +%s) - $$(date -r $(NAME) +%s))) -u +%H:%M:%S)
EXEC_MSG    := clear && echo  CREATED $(FILE_AGE) AGO && echo "--------------------"

## prod rules
#############

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_PATH)
	$(CXX) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(info CREATED $(NAME))

$(LIBS_PATH):
	$(MAKE) $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(DIR_DUP)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_PATH)); do $(MAKE) $$f clean; done
	$(RM) $(OBJS) $(DEPS) $(NAME)
	$(info REMOVED $(OBJS))
	$(info REMOVED $(DEPS))
	$(info REMOVED $(NAME))

re:
	$(MAKE) clean
	$(MAKE) all

## dev builds
#############

sure: CXXFLAGS  := -Wno-everything -Wno-unused
sure: all

asan: CXXFLAGS  += $(DEVFLAGS)
asan: CXXFLAGS  += -fsanitize=address,undefined,vptr
asan: CXXFLAGS  += -fno-optimize-sibling-calls
asan: LDFLAGS   += -g -fsanitize=address,undefined,vptr
asan: all

## dev utils
############

exec: $(NAME)
	$(EXEC_MSG)
	-./$(NAME)

leak:
	$(MAKE) re CXXFLAGS="$(CXXFLAGS) $(DEVFLAGS)"
	-$(LEAKS) ./$(NAME)

test:
	-$(TESTS)

############

init:
	-[ -d "src" ] && [ -d "include" ] && [ -d "test" ] && echo "Already done."
	-[ -d "src" ] || (mkdir "src" && echo "CREATED src")
	-[ -d "include" ] || (mkdir "include" && echo "CREATED include")
	-[ -d "test" ] || (mkdir "test" && echo "CREATED test")

ifeq ("$(SRCS)","")

srcs:
	find src -type f -name "*.cpp" | awk -F/ '{print "\t" $$NF " \\"}' > .SRCS
	sed -i '/^SRCS        := \\/ r .SRCS' Makefile
	echo "Sources added."
	rm .SRCS

else

srcs:
	echo "Find source files…"
	sed -i '/\w\.cpp \\/d' Makefile
	find src -type f -name "*.cpp" | awk -F/ '{print "\t" $$NF " \\"}' > .SRCS
	sed -i '/^SRCS        := \\/ r .SRCS' Makefile
	echo "Sources updated."
	rm .SRCS

endif

help:
	$(info  PROD RULES:)
	$(info  make all - production build, default rule)
	$(info  make clean - remove all build files)
	$(info  make re - clean + all)
	$(info  )
	$(info  DEV BUILDS:)
	$(info  make sure - compile without any warning or errors)
	$(info  make asan - compile with fsanitize)
	$(info  )
	$(info  DEV UTILS:)
	$(info  make leak - re make + exec via valgrind/leaks)
	$(info  make exec - execute)
	$(info  make test - execute tests)
	$(info  )
	$(info  make init - set the project structure)
	$(info  make srcs - init / update sources)
	$(info  make help - rules documentation)

## options
##########

.PHONY: clean re
.PHONY: help leak exec test srcs init
.SILENT:
