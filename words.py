import requests
# This script just yoinks words for our random word game

# URL of a freely available word list (for example, the MIT 10000 most frequent words)
url = "https://raw.githubusercontent.com/dwyl/english-words/master/words.txt"

response = requests.get(url)
words = response.text.splitlines()

with open("word_list.txt", "w") as file:
    file.write(",".join(words))

print(f"Total words: {len(words)}")

