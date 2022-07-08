from probability import *


def main():
    wetgrass = BayesNet([
        ('Rain', '', 0.2),
        ('Sprinkler', '', 0.1),
        ('Watson', 'Rain', {T: 1, F: 0.2}),
        ('Holmes', 'Sprinkler Rain',
         {(T, T): 1, (T, F): 0.9, (F, T): 1, (F, F): 0})])

    # P(R|H)
    print(enumeration_ask('Rain', {'Holmes': T}, wetgrass)[T])
    # print(enumeration_ask('Rain', {'Holmes': T}, wetgrass).show_approx())
    # print(enumeration_ask('Holmes', {}, wetgrass).show_approx())
    # print(enumeration_ask('Watson', {'Holmes': T}, wetgrass).show_approx())
    # print(enumeration_ask('Holmes', {'Rain': T}, wetgrass).show_approx())
    
if __name__ == "__main__":
    main()
