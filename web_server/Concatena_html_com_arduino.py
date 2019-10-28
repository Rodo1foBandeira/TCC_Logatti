with open('Index.html', 'r') as reader, open('Index.txt', 'w') as writer:
   lines = map(lambda x: 'client.println("' + x[:-1].strip().replace('"', "'") + '");\n', reader.readlines())	
   writer.writelines(lines)
