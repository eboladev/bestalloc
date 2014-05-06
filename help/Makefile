all: help

html:
	cd ./docs/; ./generate_html.sh;	cd ..

help:
	qcollectiongenerator helpcollection.qhcp -o helpcollection.qhc

clean:
	rm -f *.qch
	rm -f *.qhc
