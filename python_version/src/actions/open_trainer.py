from src.actions._base_action import _BaseAction
from studio import Studio
from src.customers import CheapCustomer, FullBodyCustomer, HeavyMuscleCustomer, SweatyCustomer
from src.actions.order import Order

class OpenTrainer(_BaseAction):
    def __init__(self, action_str: str):
        self.action_str = action_str
        self.trainer_id = action_str.split(" ")[1]
        self.customers_list = action_str.split(" ")[2:]

    def act(self, studio: Studio) -> None:
        trainer = studio.get_trainer(self.trainer_id)
        # relevant_customers = studio.get_customers(self.relevant_customers)

        if trainer is None:
            print("Workout session doesn't exist or is already open")
        elif trainer.open == False:
            print("Workout session doesn't exist or is already open")
        else:
            pass

        # create customers
        self.customers = self._create_customers()

        # # make orders
        # order_class = Order(trainer, customers)
        # order_class.act(studio)
        
        self.__complete()


    def toString(self) -> str:
        raise NotImplementedError

    def _create_customers(self):
        customers = []
        for customer_description in self.customers_list:
            name = customer_description.split(",")[0]
            ordering_strategy = customer_description.split(",")[1]
            customer = self._get_customer(name, ordering_strategy)
            customers.append(customer)
        return customers

    def _get_customer(self, name, ordering_strategy):
        if ordering_strategy == "chp":
            customer = CheapCustomer(name)
            
        elif ordering_strategy == "fbd":
            customer = FullBodyCustomer(name)
            
        elif ordering_strategy == "mcl":
            customer = HeavyMuscleCustomer(name)

        elif ordering_strategy == "swt":
            customer = SweatyCustomer(name)
        else:
            raise ValueError(f"got invalid ordering strategy {ordering_strategy}")

        return customer