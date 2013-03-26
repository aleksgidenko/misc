"""
A simple Qt Window using QWidget
"""

import sys
from PyQt4 import QtGui

def main():
	# create an application object
	app = QtGui.QApplication(sys.argv)

	# create a window,
	# (any QWidget that has no parent will become a window)
	win = QtGui.QWidget()
	win.resize(640, 480)
	win.setWindowTitle('Simple Window')
	win.show()

	# enter application mainloop and return exit status
	# to sys.exit()
	sys.exit(app.exec_())

if __name__ == '__main__':
	main()

