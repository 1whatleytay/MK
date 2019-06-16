import yaml

globalMethods = '#include <Methods.h>\n\n'
targetMethods = '#include <Methods.h>\n\n'

globalMethods += 'const MethodInfo globalMethods[] = {\n'
targetMethods += 'const MethodInfo targetMethods[] = {\n'

definitions = '#ifndef MK_METHODS_H\n#define MK_METHODS_H\n\n#include <MethodInfo.h>\n\n'


def add_methods(element):
    out = ''
    for entry in element:
        for name, method in entry.items():
            # Entry
            out += '\t{"' + name + '", '

            # Params
            if not method['params']:
                out += '{}, '
            else:
                out += '{\n'
                for paramEntry in method['params']:
                    for paramName, param in paramEntry.items():
                        # Add Param
                        out += '\t\t{'
                        out += '"' + paramName + '", '
                        out += 'Params::' + param['type']
                        if 'values' in param:
                            out += ', {'
                            for value in param['values']:
                                out += '"' + value + '", '
                            out += '}'
                            if 'optional' in param:
                                out += ', ' + str(param['optional']).lower()
                        elif 'optional' in param:
                            out += ', {}, ' + str(param['optional']).lower()
                        out += '},\n'
                out += '\t}, '

            # Source
            out += '"' + method['source'] + '"'

            out += '},\n'
    return out


with open('methods.yml', 'r') as stream:
    try:
        info = yaml.safe_load(stream)

        globalMethods += add_methods(info['globalMethods'])
        targetMethods += add_methods(info['targetMethods'])

        definitions += 'extern const MethodInfo globalMethods[' + str(len(info['globalMethods'])) + '];\n'
        definitions += 'extern const MethodInfo targetMethods[' + str(len(info['targetMethods'])) + '];\n'
    except yaml.YAMLError as e:
        print(e)

globalMethods += '};'
targetMethods += '};'

definitions += '\n#endif //MK_METHODS_H'

with open('GlobalMethods.cpp', 'w+') as stream:
    stream.write(globalMethods)
with open('TargetMethods.cpp', 'w+') as stream:
    stream.write(targetMethods)
with open('include/Methods.h', 'w+') as stream:
    stream.write(definitions)

print('Done.')
