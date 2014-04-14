BINDIR := bin
BIN_SRC := bestalloc
BIN_TST := tests
CODEDIR_SRC := src
CODEDIR_TST := tst


.PHONY: main

main:	$(BINDIR) bestalloc test run_tests

$(BINDIR):
	mkdir -p $(BINDIR) && mkdir -p $(BINDIR)/$(BIN_SRC) && mkdir -p $(BINDIR)/$(BIN_TST)

bestalloc: 
	cd $(BINDIR)/$(BIN_SRC) && qmake ../../$(CODEDIR_SRC) && make 
test:
	cd $(BINDIR)/$(BIN_TST) && qmake ../../$(CODEDIR_TST) && make 

run_tests:
	echo "Running unit tests:" && $(BINDIR)/$(BIN_TST)/test

clean:
	rm -rf bin

