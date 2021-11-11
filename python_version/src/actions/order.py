from src.actions._base_action import _BaseAction
from studio import Studio

class Order(_BaseAction):
    def __init__(self, action_str: str):
        self.action_str = action_str
        self.trainer_id = action_str.split(" ")[1]


    def act(self, studio: Studio) -> None:
        trainer = studio.get_trainer(self.trainer_id)

        if self.trainer is None:
            print("Workout session doesn't exist or is already open")
            return
        elif self.trainer.open == False:
            print("Workout session doesn't exist or is already open")
            return
        else:
            pass

        # make orders
        for customer in trainer.customers:
            list_of_workouts = customer.order(trainer.workout_options)
            name = customer.name

            for workout in list_of_workouts:
                print(f"{name} is doing {workout}")
                
        self.__complete()

        