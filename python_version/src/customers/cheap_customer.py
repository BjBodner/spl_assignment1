from src.customers._customer import _Customer
from src.workout import Workout
from typing import List

class CheapCustomer(_Customer):
    def __init__(self, name: str, strategy: str) -> None:
        super().__init__(name, strategy)

    def order(self, workout_options) -> List[Workout]:

        # get workout option with lowest price
        cheapest_workout_idx = self._get_cheapest_workout_idx(workout_options)
        
        # orders single workout at idx "cheapest_workout_idx"
        list_of_workouts = [workout_options[cheapest_workout_idx]]
        return list_of_workouts

    def _get_cheapest_workout_idx(self, workout_options) -> int:
        cheapest_workout_idx = 0
        best_price = 1e8
        lowest_id = 1e8

        for i in range(len(workout_options)):
            workout_option = workout_options[i]
            price = workout_option.price
            id = workout_option.id


            is_best_price = (price < best_price)
            equal_price_and_lowest_id = (price == best_price) and (id < lowest_id)

            if is_best_price or equal_price_and_lowest_id:
                cheapest_workout_idx = i
                best_price = price
                lowest_id = id

        return cheapest_workout_idx