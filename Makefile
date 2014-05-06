TARGET := bestalloc
BINDIR := bin
BIN_SRC := bestalloc
BIN_TST := tests
CODEDIR_SRC := src
CODEDIR_TST := tst

HELP_DIR := help
HELP_FILE := help.qch
HELP_COLLECTION := helpcollection.qhc

.PHONY: main

main: $(BINDIR) bestalloc help_files test run_tests

$(BINDIR):
	mkdir -p $(BINDIR) && mkdir -p $(BINDIR)/$(BIN_SRC) && mkdir -p $(BINDIR)/$(BIN_TST)

bestalloc: 
	cd $(BINDIR)/$(BIN_SRC) && qmake ../../$(CODEDIR_SRC) && make 

test:
	cd $(BINDIR)/$(BIN_TST) && qmake ../../$(CODEDIR_TST) && make 

run_tests:
	echo "Running unit tests:" && $(BINDIR)/$(BIN_TST)/test

help_files:
	$(MAKE) -C help/

build: clean
	dpkg-buildpackage -rfakeroot -uc -us

clean:
	$(MAKE) -C help/ clean
	if test -d $(BINDIR); then rm -r $(BINDIR); fi

install: main
	install $(BINDIR)/$(BIN_SRC)/$(TARGET) $(DESTDIR)$(INSTALLDIR)
	install $(HELP_DIR)/$(HELP_FILE) $(DESTDIR)$(OPTDIR)
	install $(HELP_DIR)/$(HELP_COLLECTION) $(DESTDIR)$(OPTDIR)
