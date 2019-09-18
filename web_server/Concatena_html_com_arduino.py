with open('C:/Projetos/TCC_Logatti/Layout/Index.html', 'r') as reader, open('C:/Projetos/TCC_Logatti/Layout/Index.txt', 'w') as writer:
   lines = map(lambda x: 'client.println("' + x[:-1].strip().replace('"', "'") + '");\n', reader.readlines())	
   writer.writelines(lines)