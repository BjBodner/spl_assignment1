from src.customers._customer import _Customer
from src.workout import Workout
from typing import List
import numpy as np

class HeavyMuscleCustomer(_Customer):
    def __init__(self, name: str, strategy: str) -> None:
        super().__init__(name, strategy)

    def order(self, workout_options) -> List[Workout]:

        # get all the anaerobic workout idxs
        anaerobic_workout_idxs = self._get_all_anaerobic_workout_idxs(workout_options)
        
        # sort anerobic exercises based on price (expensive first)
        sorted_anaerobic_workout_idxs = self._sort_prices(workout_options, anaerobic_workout_idxs)

        # orders workouts
        list_of_workouts = []
        for idx in sorted_anaerobic_workout_idxs:
            list_of_workouts.append(workout_options[idx])

        return list_of_workouts

    def _get_all_anaerobic_workout_idxs(self, workout_options) -> int:
        anaerobic_workout_idxs = []
        for i in range(len(workout_options)):
            workout_option = workout_options[i]
            if workout_option.type == "anaerobic":
                anaerobic_workout_idxs.append(i)

        return anaerobic_workout_idxs

    def _sort_prices(self, workout_options: list, anaerobic_workout_idxs: list):
        prices = []
        for idx in anaerobic_workout_idxs:
            workout_option = workout_options[idx]
            prices.append(workout_option.price)
        
        sorted_anaerobic_workout_idxs = list(np.argsort(prices))
        return sorted_anaerobic_workout_idxs