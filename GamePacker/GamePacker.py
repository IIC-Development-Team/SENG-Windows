import sys
import os
import typing
from PyQt5 import QtCore, QtWidgets, QtGui
from PyQt5.QtWidgets import QApplication, QWidget
try:
    from PyQt5.QtCore import QString
except ImportError:
    QString = str
    
class Window(QtWidgets.QMainWindow):
    def __init__(self, width, height, x = 50, y = 50):
        super(Window, self).__init__()
        
        self.setFixedSize(width, height)
        self.setWindowTitle("SENG - GamePacker")
        self.setCentralWidget(QtWidgets.QWidget(self))
        self.layout = QtWidgets.QVBoxLayout()
        self.stackedlayout = QtWidgets.QStackedWidget()
        self.questionsno = 0;
        self.menu = QtWidgets.QWidget()
        self.stackedlayout.addWidget(self.menu)
        self.show()
        

if(__name__ == "__main__"):
    app = QApplication(sys.argv)
    window = Window(1280, 720)
    window.setWindowTitle("SENG - GamePacker v1.0")

    sys.exit(app.exec_())