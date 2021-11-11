
from studio import Studio

ERROR_STR = "ERROR"
COMPLETED_STR = "COMPLETED"

class _BaseAction:
    def __init__(self, status_flag: str = None) -> None:
        self.status_flag = status_flag
        pass

    def act(self, studio: Studio) -> None:
        raise NotImplementedError

    def toString(self) -> str:
        raise NotImplementedError

    def __complete(self) -> None:
        self.status_flag = COMPLETED_STR

    def __error(self, errorMsg: str) -> None:
        self.status_flag = ERROR_STR
        print(f"Error: {errorMsg}")

