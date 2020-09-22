import yaml

globalMethods = '#include <resources/resources.h>\n\n'
targetMethods = '#include <resources/resources.h>\n\n'
items = '#include <resources/resources.h>\n\n'
entities = '#include <resources/resources.h>\n\n'

globalMethods += 'const std::vector<MethodData> globalMethods = {\n'
targetMethods += 'const std::vector<MethodData> targetMethods = {\n'
items += 'const std::vector<std::string> items = {\n'
entities += 'const std::vector<std::string> entities = {\n'


def add_methods(element):
    out = ''
    for entry in element:
        for name, method in entry.items():
            # Entry
            out += '    { "' + name + '", '

            # Params
            if not method['params']:
                out += '{ }, '
            else:
                out += '{\n'
                for paramEntry in method['params']:
                    for paramName, param in paramEntry.items():
                        # Add Param
                        out += '        { '
                        out += '"' + paramName + '", '
                        out += 'Param::Type::' + param['type']
                        if 'values' in param:
                            out += ', {'
                            for value in param['values']:
                                out += '"' + value + '", '
                            out += '}'
                            if 'optional' in param:
                                out += ', ' + str(param['optional']).lower()
                        elif 'optional' in param:
                            out += ', { }, ' + str(param['optional']).lower()
                        out += ' },\n'
                out += '    }, '

            # Source
            out += '"' + method['source'] + '"'

            out += ' },\n'
    return out


with open('resources.yml', 'r') as stream:
    try:
        info = yaml.safe_load(stream)

        globalMethods += add_methods(info['globalMethods'])
        targetMethods += add_methods(info['targetMethods'])

        for entry in info['items']:
            items += '    "' + entry + '",\n'

        for entry in info['entities']:
            entities += '    "' + entry + '",\n'
    except yaml.YAMLError as e:
        print(e)

globalMethods += '};\n\n'
targetMethods += '};\n\n'
items += '};\n\n'
entities += '};\n\n'

globalMethods += 'const std::vector<MethodData> &getGlobalMethodData() { return globalMethods; }\n'
targetMethods += 'const std::vector<MethodData> &getGlobalMethodData() { return targetMethods; }\n'
items += 'const std::vector<std::string> &getItemNames() { return items; }\n'
entities += 'const std::vector<std::string> &getEntityNames() { return entities; }\n'

with open('src/global_methods.cpp', 'w+') as stream:
    stream.write(globalMethods)
with open('src/target_methods.cpp', 'w+') as stream:
    stream.write(targetMethods)
with open('src/items.cpp', 'w+') as stream:
    stream.write(items)
with open('src/entities.cpp', 'w+') as stream:
    stream.write(entities)

print('Done.')
