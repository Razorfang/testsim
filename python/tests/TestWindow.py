from PyQt5.QtWidgets import QWidget, QPushButton, QHBoxLayout, QVBoxLayout, QLineEdit, QLabel
from PyQt5.QtGui import QIntValidator

class _DurationInput(QWidget):
    def __init__(self, rangeMin, rangeMax):
        super().__init__()

        editor = QLineEdit()
        editor.setValidator(QIntValidator(rangeMin, rangeMax))

        desc = QLabel(f"Please enter a test duration between {rangeMin} and {rangeMax} seconds: ")

        layout = QHBoxLayout()
        layout.addWidget(desc)
        layout.addWidget(editor)
        self.setLayout(layout)


class _CriteriaInput(QWidget):
    def __init__(self):
        super().__init__()

        desc = QLabel("Please enter the limits for this test:")

        limitWidget = QWidget()
        limitLayout = QHBoxLayout()
        limitLayout.addWidget(QLineEdit())
        limitLayout.addWidget(QLabel(" <= test result <= "))
        limitLayout.addWidget(QLineEdit())
        limitWidget.setLayout(limitLayout)

        fullLayout = QVBoxLayout()
        fullLayout.addWidget(desc)
        fullLayout.addWidget(limitWidget)
        self.setLayout(fullLayout)

class _StartButton(QPushButton):
    def __init__(self):
        super().__init__("Start")
        self.setToolTip("Start test execution")

class _StopButton(QPushButton):
    def __init__(self):
        super().__init__("Stop")
        self.setToolTip("Force test execution to stop")

class TestWindow(QWidget):
    def __init__(self):
        super().__init__()

        topWidget = QWidget()
        topLayout = QVBoxLayout()
        topLayout.addWidget(_DurationInput(0, 600))
        topLayout.addWidget(_CriteriaInput())
        topWidget.setLayout(topLayout)

        bottomWidget = QWidget()
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(_StartButton())
        bottomLayout.addWidget(_StopButton())
        bottomWidget.setLayout(bottomLayout)

        fullLayout = QVBoxLayout()
        fullLayout.addWidget(topWidget)
        fullLayout.addWidget(bottomWidget)
        self.setLayout(fullLayout)

