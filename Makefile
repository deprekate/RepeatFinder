all:
	python3 setup.py install --user
clean:
	pip3 uninstall -y RepeatFinder
	rm -fr build
	rm -fr dist
	rm -fr repeatfinder.egg-info
