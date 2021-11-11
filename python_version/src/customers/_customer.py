

from workout import Workout

from typing import List

class _Customer:

    def __init__(self, id: int, name: str, ordering_strategy: str) -> None:
        self.id = id
        self.name = name
        ordering_strategy = ordering_strategy

    def order(self, workout_options) -> List[Workout]:
        raise NotImplementedError