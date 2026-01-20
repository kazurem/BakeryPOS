import sys

from PySide6.QtWidgets import QApplication, QMainWindow, QWidget

class BakeryWindow(QMainWindow):
    """
    BakeryPOS main window
    """
    def __init__(self):
        super().__init__()
        self.setWindowTitle("BakeryPOS")

class BakeryPOS:
    """
    Bakery POS app
    """
    def run(self) -> None:
        """
        launches the main loop
        """
        self.app = QApplication(sys.argv)
        window = BakeryWindow()
        window.show()
        self.app.exec()




