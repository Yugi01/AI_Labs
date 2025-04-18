initial_input = input()
umbrella = initial_input.split(' ')

pRain = 0.7
pNotRain = 0.3
pUmbrella = 0.9
pNotUmbrella = 0.2

def forward(observation):

    initial=0.5
    print('Timestep 0: 0.5')
    for i in range(len(observation)):
        #umbrella
        # print(initial)
        if(observation[i]=='1'):
            probRain = initial*pRain+(1-initial)*pNotRain
            probNotRain = (1-initial)*pRain+initial*pNotRain
            # print(probNotRain)
            relativeRain = probRain * pUmbrella
            relativeNoRain = probNotRain * pNotUmbrella
            totalRelativeProb = relativeRain + relativeNoRain
            finalProb = relativeRain/totalRelativeProb
            # print(finalProb)
        else:
            probRain = initial*pRain+(1-initial)*pNotRain
            probNotRain = (1-initial)*pRain+initial*pNotRain
            relativeRain = probRain * (1-pUmbrella)
            relativeNoRain = probNotRain * (1-pNotUmbrella)
            totalRelativeProb = relativeRain + relativeNoRain    
            finalProb = relativeRain/totalRelativeProb
        print(f'Timestep {i+1}: {finalProb:.3f}')
        initial = finalProb

forward(umbrella)