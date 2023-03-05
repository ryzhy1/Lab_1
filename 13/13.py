with(open('input.txt')) as file :
    prices = list(map(int, file.readline().split()))



def we_are_still_friends(prices):
    total_cost = sum(prices)

    if len(prices) < 3 or total_cost % 3 != 0:
        return 0
    else:
        prices.sort()
        prices = prices[-1:0:-1]

        part_of_each = total_cost // 3

        for _ in range(3):
            souvenirs_of_person = []
            index_of_souvenir = 0

            while sum(souvenirs_of_person) < part_of_each:
                if len(prices) - 1 < index_of_souvenir:
                    return 0
                else:
                    adding_souvenir = prices[index_of_souvenir]

                    if sum(souvenirs_of_person) + adding_souvenir <= part_of_each:
                        souvenirs_of_person.append(adding_souvenir)
                        prices.pop(index_of_souvenir)

                    else:
                        index_of_souvenir += 1

        if prices is []:
            return 1


result = we_are_still_friends(prices)

f = open('output.txt', 'w')
f.write(str(result))