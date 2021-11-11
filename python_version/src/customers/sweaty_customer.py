from src.customers._customer import _Customer
from src.workout import Workout
from typing import List
import numpy as np

class SweatyCustomer(_Customer):
    def __init__(self, id: int, name: str, ordering_strategy: str) -> None:
        super().__init__(id, name, ordering_strategy)

    def order(self, workout_options) -> List[Workout]:

        # get idxs of relevant workouts
        all_cardio_idxs = self._get_all_cardio_idxs(workout_options, requested_type="cardio", requested_price="cheapest")

        # orders workouts
        list_of_workouts = []
        for idx in all_cardio_idxs:
            list_of_workouts.append(workout_options[idx])

        return list_of_workouts

    def _get_all_cardio_idxs(self, workout_options: list) -> list:
        
        all_cardio_idxs = []
        for i in range(len(workout_options)):
            workout_option = workout_options[i]
            type_ = workout_option.type

            if (type_ == "cardio"):
                all_cardio_idxs.append(i)


        return all_cardio_idxs
