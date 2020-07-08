# By submitting this assignment, I agree to the following:
#  "Aggies do not lie, cheat, or steal, or tolerate those who do"
#  "I have not given or received any unauthorized aid on this assignment"
#
# Name:        Marcel Thio, Sunjeeth Chandramohan, Reagan Schwartz
# Section:     503
# Assignment:  Activity3
# Date:        8 December 2018

import Disease as d
import matplotlib.pyplot as plt

def simulate(num = 1000, parameter = 1):
    tra2 = []
    if parameter == 1:
        res, rec, act, tra = d.parameters(num)
    elif parameter == 2:
        res, rec, act, tra = d.parameters2(num)
    else:
        res, rec, act, tra, tra2 = d.act2para(num)


    inf = []    # those who are infected
    immun = []  # those who are immune
    healthy = [] # those who are not infected nor immune
    for n in range(0,len(res)):
        healthy.append(n)

    # random person is picked
    inf.append(d.ran.randint(0,len(res)))
    healthy.remove(inf[0])

    # ------------statistics-variables-------
    num_inf = [1]
    num_new_inf = [1]
    num_immune = [0]
    num_not_inf =[len(healthy)]
    # ---------------------------------------

    # days of infection plays out
    day = 0
    days = [day]
    while(len(inf)):
        new_inf = d.infect(inf,res,act,tra,immun,tra2)          # get newly infected
        rec = d.recovery(inf,rec)                          # update recovery of those infected
        inf, immun = d.immunity(rec, inf, immun)           # check who became immune
        inf,healthy = d.new_infected(new_inf,inf,healthy)  # update infected and healthy

        day += 1
        days.append(day)

        # ------------statistics-------
        num_inf.append(len(inf))
        num_new_inf.append(len(new_inf))
        num_immune.append(len(immun))
        num_not_inf.append(len(healthy))
        print('\n\nDay',day)
        print('# Infected: ',len(inf))
        print('# New Infected: ',len(new_inf))
        print('# Immune: ',len(immun))
        print('# Healthy',len(healthy))
        # ---------------------------------------

    # ---------plot data--------------------
    plt.plot(days,num_inf,label = '# infected')
    plt.plot(days,num_new_inf,label= 'infection rate')
    plt.plot(days,num_immune,label = '# immune')
    plt.plot(days,num_not_inf,label = '# not infected')
    plt.legend()
    plt.show()
    # Give statistics
    print('\n----------------------------\nLength of Outbreak: ',day)
    print('Amount of people not infected: ',len(healthy))
    print('Maximum number of people infected in one day: ',max(num_inf))
    statistics ='''\n\nLength of Outbreak: {}
    Amount of people not infected: {}
    Maximum number of people infected in one day: {}'''.format(day,len(healthy),max(num_inf))

    return statistics


# Program Runner

# 4
stat1 = simulate(1000,1)
# 5
stat2 = simulate(1000,2)
# 6
stat3 = simulate(1000,3)

# Conclusion

print('----------------------------')
print('\nSimulation 1:',stat1)
print('\nSimulation 2:',stat2)
compare = '''\nGiven a reasonable value for resistance and transmission activity
parameter is the most important in changing the numbers of person
who get sick.'''
print(compare)
print('For # 6 simulation included 5 different friends for everyone with different \ntransmission values per person',stat3)

