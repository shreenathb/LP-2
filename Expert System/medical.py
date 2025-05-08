

def diab_score(fasting_sugar, post_meal_sugar, symptoms, history_diab):
    score = 0

    if fasting_sugar >= 125:
        score+= 2
    if post_meal_sugar >= 200:
        score+=2
    if history_diab:
        score+= 1

    count = len([value for value in symptoms.values() if value == 'yes'])

    if(count > 0):
        score += 1
    
    if score >= 4:
        return "High"
    elif score >= 2:
        return "moderate"
    else:
        return "low"
    



def eval_diab_risk(fasting_sugar, post_meal_sugar, symptoms, history_diab):
    diab_risk = False
    risk_level = diab_score(fasting_sugar, post_meal_sugar, symptoms, history_diab)
    print(risk_level)
    if fasting_sugar >= 125 and post_meal_sugar >= 200:
        diab_risk = True
        if history_diab:
            print('Critical levels of sugar in blood + history present')
        else:
            print('Consult a doc as critical level of sugar is present')
    elif fasting_sugar >= 100 and post_meal_sugar >= 140:
        diab_risk = True
        print('Exercise + reguarly monitor sugar levels')
    else:
        print('You dont have diabetes')

    return diab_risk

def eval_hypertension_risk(systolic_bp, diastolic_bp, symptoms):
    if(systolic_bp>= 140 and diastolic_bp >= 100):
        if symptoms['chest pain'] == 'yes':
            print('consult a doc immediately')
        print('high bp')
    elif(systolic_bp>= 120 and diastolic_bp >= 80):
        print('risk of high bp')
    else:
        print('not at risk of high bp')

def final_summary(diab_risk, hypertension_risk, age):
    if not diab_risk and not hypertension_risk:
        print('You are in good health')
        if(age >= 45):
            print('regular checkups are advised')

def main():
    age = int(input('Enter your age: '))
    systolic_bp = int(input('Enter your s bp: '))
    diastolic_bp = int(input('Enter your d bp: '))
    post_meal_sugar = int(input('Enter your post meal sugar: '))
    fasting_sugar = int(input('Enter your f sugar: '))

    history_diab = input('history of diabetes: ').lower()

    symptoms = {
        'chest pain' : input('chest pain'),
        'fever' : input('fever'),
        'frequent urination' : input('frequent urination'),
        'fatigue' : input('fatigue'),
        'thirst' : input('thirst')
    }

    print('Report')

    diab_risk = eval_diab_risk(fasting_sugar, post_meal_sugar, symptoms, history_diab)
    hypertension_risk = eval_hypertension_risk(systolic_bp, diastolic_bp, symptoms)
    final_summary(diab_risk, hypertension_risk, age)

main()