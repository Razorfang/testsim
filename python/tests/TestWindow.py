from PyQt5.QtWidgets import QWidget, QPushButton, QHBoxLayout, QVBoxLayout, QLineEdit, QLabel
from PyQt5.QtGui import QIntValidator

class _DurationInput(QWidget):
    def __init__(self, lineEdit, rangeMin, rangeMax):
        super().__init__()

        lineEdit.setValidator(QIntValidator(rangeMin, rangeMax))

        desc = QLabel(f"Please enter a test duration between {rangeMin} and {rangeMax} seconds: ")

        layout = QHBoxLayout()
        layout.addWidget(desc)
        layout.addWidget(lineEdit)
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
    def __init__(self, clickEvent):
        super().__init__("Start")
        self.setToolTip("Start test execution")
        self.clicked.connect(clickEvent)

class _StopButton(QPushButton):
    def __init__(self, clickEvent):
        super().__init__("Stop")
        self.setToolTip("Force test execution to stop")
        self.clicked.connect(clickEvent)

class TestWindow(QWidget):
    def __init__(self, onStartEvent, onStopEvent):
        super().__init__()

        self.durationLineEdit = QLineEdit()

        topWidget = QWidget()
        topLayout = QVBoxLayout()
        topLayout.addWidget(_DurationInput(self.durationLineEdit, 0, 600))
        topLayout.addWidget(_CriteriaInput())
        topWidget.setLayout(topLayout)

        bottomWidget = QWidget()
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(_StartButton(onStartEvent))
        bottomLayout.addWidget(_StopButton(onStopEvent))
        bottomWidget.setLayout(bottomLayout)

        fullLayout = QVBoxLayout()
        fullLayout.addWidget(topWidget)
        fullLayout.addWidget(bottomWidget)
        self.setLayout(fullLayout)

    def getTestDuration(self):
        return self.durationLineEdit.text()
