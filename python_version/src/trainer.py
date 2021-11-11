

class Trainer:

    def __init__(self, capacity: int, open: bool = True, workout_plans: list = [], customers: list = [], id: int = 0) -> None:
        self.capacity = capacity
        self.open = open
        self.workout_plans = workout_plans
        self.customers = customers
        self.id = id