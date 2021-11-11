from src.actions._base_action import _BaseAction
from studio import Studio


class OpenTrainer(_BaseAction):
    def __init__(self):
        pass

    def act(self, studio: Studio) -> None:
        raise NotImplementedError

    def toString(self) -> str:
        raise NotImplementedError