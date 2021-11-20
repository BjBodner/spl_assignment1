

from typing import Any


class Studio:

    def __init__(self, trainers: list = None, workout_plan: Any = None) -> None:
        self.trainers = trainers
        self.workout_plan = workout_plan
