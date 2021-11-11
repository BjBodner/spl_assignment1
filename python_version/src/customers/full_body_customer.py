from src.customers._customer import _Customer
from src.workout import Workout
from typing import List
import numpy as np

class FullBodyCustomer(_Customer):
    def __init__(self, id: int, name: str, ordering_strategy: str) -> None:
        super().__init__(id, name, ordering_strategy)

    def order(self, workout_options) -> List[Workout]:

        # get idxs of relevant workouts
        cheapest_cardio_workout_idx = self._get_best_workout_idx(workout_options, requested_type="cardio", requested_price="cheapest")
        most_expensive_mixtype_workout_idx = self._get_best_workout_idx(workout_options, requested_type="mixed", requested_price="most_expensive")
        cheapest_anaerobic_workout_idx = self._get_best_workout_idx(workout_options, requested_type="anaerobic", requested_price="cheapest")
        all_workout_idxs = [cheapest_cardio_workout_idx, most_expensive_mixtype_workout_idx, cheapest_anaerobic_workout_idx]

        # orders workouts
        list_of_workouts = []
        for idx in all_workout_idxs:
            list_of_workouts.append(workout_options[idx])

        return list_of_workouts

    def _get_best_workout_idx(self, workout_options: list, requested_type: str, requested_price: str) -> int:
        cheapest_workout_idx = 0
        best_price = 1e8 if requested_price == "cheapest" else 0
        lowest_id = 1e8
        for i in range(len(workout_options)):
            workout_option = workout_options[i]
            price = workout_option.price
            type_ = workout_option.type
            id = workout_option.id

            is_best_price = (price < best_price) if (requested_price == "cheapest") else (price < best_price)
            is_requested_type = (type_ == requested_type)
            equal_price_and_lowest_id = (price == best_price) and (id < lowest_id)


            if (is_best_price or equal_price_and_lowest_id) and is_requested_type:
                best_workout_idx = i
                best_price = price
                lowest_id = id

        return best_workout_idx
