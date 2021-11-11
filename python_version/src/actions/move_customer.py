from src.actions._base_action import _BaseAction
from studio import Studio

class MoveCustomer(_BaseAction):
    def __init__(self, action_str: str):
        self.action_str = action_str
        self.customer_id = action_str.split(" ")[1]
        self.current_trainer_id = action_str.split(" ")[2]
        self.new_trainer_id = action_str.split(" ")[3]


    def act(self, studio: Studio) -> None:
        current_trainer = studio.get_trainer(self.current_trainer_id)
        new_trainer = studio.get_trainer(self.new_trainer_id)

                
        self.__complete()

        