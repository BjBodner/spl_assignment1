

from workout import Workout

from typing import List

class _Customer:

    id_ = 0
    @classmethod
    def get_id(cls) -> int:
        cls.id_ += 1
        return cls.id_

    def __init__(self, name: str, strategy: str) -> None:
        self.id = _Customer.get_id()
        self.name = name
        self.strategy = strategy

    def order(self, workout_options) -> List[Workout]:
        raise NotImplementedError