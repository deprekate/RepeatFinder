all:
	python3 setup.py install --user
clean:
	pip3 uninstall -y RepeatFinder
	rm -fr build
	rm -fr dist
	rm -fr repeatfinder.egg-info

upload:
	python3 setup.py sdist bdist_wheel
	python3 -m twine upload dist/*
