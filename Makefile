.PHONY: all run clean submit

# Course tree: DRAMSim2, RISC-V toolchain, test programs.
CSE502?=/opt/shared/cse502

# Program to run.  Anything on the command line starting with '+' goes to
# Verilator (plusargs); everything else is passed to the program as argv.
PROG=$(CSE502)/tests/wp1/prog1
#PROG=$(CSE502)/tests/bbl.bin

TRACE?=--trace
HAVETLB=n
FULLSYSTEM=n

# Verilator needs a package parsed before the file that imports it, so any file
# declaring one goes first.  Detected by content, not by name.  (A package that
# imports another package still has to be ordered by hand.)
VPKGS=$(shell grep -lE '^[[:space:]]*package[[:space:]]' *.sv 2>/dev/null)
VFILES=$(VPKGS) $(filter-out $(VPKGS),$(wildcard *.sv))
CFILES=$(wildcard *.cpp)

all: obj_dir/Vtop

obj_dir/Vtop: obj_dir/Vtop.mk
	$(MAKE) -j$(shell nproc) -C obj_dir/ -f Vtop.mk CXX="ccache g++"

obj_dir/Vtop.mk: $(VFILES) $(CFILES)
	verilator -Wall -Wno-lint -O3 $(TRACE) --no-skip-identical --cc $(VFILES) --top-module top \
	--exe $(CFILES) $(CSE502)/DRAMSim2/libdramsim.so \
	-CFLAGS -I$(CSE502) -CFLAGS -g3 \
	-LDFLAGS -Wl,-rpath=$(CSE502)/DRAMSim2 \
	-LDFLAGS -lncurses -LDFLAGS -lelf -LDFLAGS -lrt

run: obj_dir/Vtop
	cd obj_dir/ && env HAVETLB=$(HAVETLB) FULLSYSTEM=$(FULLSYSTEM) ./Vtop $(PROG)

clean:
	rm -rf obj_dir/ dramsim2/results trace.vcd core

# Submitting:
#   make submit ASSIGNMENT=wp1
#   make submit ASSIGNMENT=wp2
#   make submit ASSIGNMENT=project POINTS=<n> TLB=<y|n> BP=<y|n>
# The snapshot goes to /submit/$(ASSIGNMENT); the two previous ones are kept
# as .1 and .2.  For the project you must state how many points you are
# claiming and whether the core has a TLB (HAVETLB=y works) and a branch
# predictor; this is recorded in the SUBMIT file at the top of the snapshot.
SUBMIT_DIR?=/submit
submit:
	@set -e; \
	case "$(ASSIGNMENT)" in \
	  wp1|wp2) ;; \
	  project) \
	    echo "$(POINTS)" | grep -qxE '[0-9]+' || { echo "project: set POINTS=<number>"; exit 1; }; \
	    case "$(TLB)" in y|n) ;; *) echo "project: set TLB=y or TLB=n"; exit 1;; esac; \
	    case "$(BP)"  in y|n) ;; *) echo "project: set BP=y or BP=n";   exit 1;; esac;; \
	  *) echo "usage: make submit ASSIGNMENT=wp1|wp2"; \
	     echo "       make submit ASSIGNMENT=project POINTS=<n> TLB=<y|n> BP=<y|n>"; exit 1;; \
	esac; \
	STMP=$$(mktemp -d /tmp/cse502-submit.XXXXXX); \
	cleanup() { set +e; chmod -R u+w "$$STMP" 2>/dev/null; rm -rf "$$STMP" 2>/dev/null; }; \
	trap cleanup EXIT; \
	rsync -a \
		--exclude='.git' --exclude='obj_dir/' --exclude='dramsim2/results/' \
		--exclude='*.vcd' --exclude='*.fst' --exclude='core' --exclude='.claude/' \
		--max-size=1M \
		. "$$STMP/"; \
	cd "$$STMP"; \
	{ echo "assignment=$(ASSIGNMENT)"; \
	  [ "$(ASSIGNMENT)" = project ] && echo "points=$(POINTS)" && echo "tlb=$(TLB)" && echo "bp=$(BP)"; \
	  echo "user=$(USER)"; echo "date=$$(date +%F=%T)"; } > SUBMIT; \
	git init -q; \
	git add -A; \
	git -c user.name=student -c user.email=student@cse502 commit -q -m "submit"; \
	rm -rf $(SUBMIT_DIR)/$(ASSIGNMENT).2 2>/dev/null || true; \
	mv $(SUBMIT_DIR)/$(ASSIGNMENT).1 $(SUBMIT_DIR)/$(ASSIGNMENT).2 2>/dev/null || true; \
	mv $(SUBMIT_DIR)/$(ASSIGNMENT) $(SUBMIT_DIR)/$(ASSIGNMENT).1 2>/dev/null || true; \
	mkdir -p $(SUBMIT_DIR)/$(ASSIGNMENT); \
	git archive HEAD | tar -x -C $(SUBMIT_DIR)/$(ASSIGNMENT); \
	echo "Submitted to $(SUBMIT_DIR)/$(ASSIGNMENT):"; cat $(SUBMIT_DIR)/$(ASSIGNMENT)/SUBMIT
