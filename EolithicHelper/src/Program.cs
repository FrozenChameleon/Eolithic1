/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

namespace EolithicHelper
{
    class Program
    {
        private const string FILE_COMPONENTS = "components.txt";
        private const string FILE_RESOURCE = "resources.txt";
        private const string FILE_TEMPLATE_RESOURCE_HEADER = "Template_RESOURCE.h";
        private const string FILE_TEMPLATE_RESOURCE_DEFINITIONS = "Template_RESOURCE.c";
        private const string DIR_HELPER_RESOURCES = "helper_resources";
        private const string DIR_SRC = "src";
        private const string DIR_ENGINE = "engine";
        private const string DIR_RESOURCES = "resources";
        private const string DIR_GAMESTATE = "gamestate";
        private const string KEYWORD_INCLUDE_PATH = "%strIncludePath%";
        private const string KEYWORD_RESOURCE = "%strResource%";
        private const string KEYWORD_RESOURCE_LOWER = "%strResource_lower%";
        private const string KEYWORD_RESOURCE_MANAGER = "%strResourceManager%";

        class Config
        {
        }

        static void Main(string[] args)
        {
            Console.WriteLine("Welcome to Eolithic Helper!");
            Console.WriteLine("[C] - Generate Components Boilerplate From " + FILE_COMPONENTS);
            Console.WriteLine("[R] - Generate Resource Boilerplate From " + FILE_RESOURCE);
            Console.WriteLine("[P] - Exit");

            Loop();
        }
        static void Loop()
        {
            while (true)
            {
                if (!Console.KeyAvailable)
                {
                    continue;
                }

                ConsoleKey key = Console.ReadKey().Key;
                if (key == ConsoleKey.C)
                {
                    GenerateComponentBoilerplate();
                }
                else if (key == ConsoleKey.R)
                {
                    GenerateResourceBoilerPlate();
                }
                else if (key == ConsoleKey.P)
                {
                    Environment.Exit(0);
                }
            }
        }
        static void GenerateComponentBoilerplate()
        {
            Console.WriteLine("Reading component file");

            string pathForFileComponents = Path.Combine(DIR_HELPER_RESOURCES, FILE_COMPONENTS);
            if (!File.Exists(pathForFileComponents))
            {
                Console.WriteLine("Unable to open component file");
                return;
            }

            int counter = 0;
            string[] componentFileContents = File.ReadAllLines(pathForFileComponents);

            string gameStateDataHelperString = "";
            gameStateDataHelperString += "\n";
            gameStateDataHelperString += "#define GSD_INITIAL_SIZE 4\n";
            gameStateDataHelperString += "\n";
            gameStateDataHelperString += "void GameStateDataHelper_InitAllComponentPacks(GameStateData* gsd)\n";
            gameStateDataHelperString += "{\n";

            string componentTypeString = "//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!\n\n";
            componentTypeString += "#pragma once\n";
            componentTypeString += "\n";
            componentTypeString += "#define COMPONENT_TYPE_LEN " + componentFileContents.Length + "\n";
            componentTypeString += "\n";
            componentTypeString += "typedef enum ComponentType\n";
            componentTypeString += "{\n";

            string includeThese = "";

            foreach (string component in componentFileContents)
            {
                string fileWithStruct = FindFileWithStruct(component);
                if (fileWithStruct == null)
                {
                    Console.WriteLine("Unable to find: " + component + " (missing typedef perhaps?)");
                    continue;
                }

                string fileLocation = fileWithStruct.Replace('\\', '/');
                fileLocation = fileLocation.Replace("src/engine/", "../");
                includeThese += "#include " + '"' + fileLocation + '"' + '\n';

                Console.WriteLine("Found " + component + " at " + fileWithStruct);

                Console.WriteLine("Generating boiler plate for " + component);

                string componentEnumName = "C_" + component;

                gameStateDataHelperString += "    " + "ComponentPack_Init(&gsd->mComponentPacks[" + componentEnumName + "], sizeof(" + component + "), GSD_INITIAL_SIZE);\n";

                componentTypeString += "    " + componentEnumName + " = " + counter + ",\n";

                counter += 1;

                /*
                string replaceResourceManager = components + "Manager";

                string pathToRemoveFromFileWithStruct = Path.Combine(DIR_SRC, DIR_ENGINE);
                string replaceIncludePath = fileWithStruct.Replace(pathToRemoveFromFileWithStruct, "");
                replaceIncludePath = "../" + replaceIncludePath;
                replaceIncludePath = replaceIncludePath.Replace("\\", "/");
                replaceIncludePath = replaceIncludePath.Replace("//", "/");
                replaceIncludePath = "#include " + '"' + replaceIncludePath + '"';

                string resourceManagerPathForHeader = Path.Combine(DIR_SRC, DIR_ENGINE, DIR_RESOURCES, replaceResourceManager + ".h");
                WriteTemplate(Path.Combine(DIR_HELPER_RESOURCES, FILE_TEMPLATE_RESOURCE_HEADER),
                    resourceManagerPathForHeader, replaceIncludePath, components, replaceResourceManager);

                string resourceManagerPathForDefinition = Path.Combine(DIR_SRC, DIR_ENGINE, DIR_RESOURCES, replaceResourceManager + ".c");
                WriteTemplate(Path.Combine(DIR_HELPER_RESOURCES, FILE_TEMPLATE_RESOURCE_DEFINITIONS),
                    resourceManagerPathForDefinition, replaceIncludePath, components, replaceResourceManager);
                */
            }

            gameStateDataHelperString += "}\n";
            gameStateDataHelperString = ("//THIS CODE IS AUTOMATICALLY GENERATED, DO NOT EDIT!\n\n#include \"GameStateDataHelper.h\"\n#include \"ComponentType.h\"\n\n" + includeThese + gameStateDataHelperString);

            componentTypeString += "} ComponentType;\n";

            {
                string componentTypePath = Path.Combine(DIR_SRC, DIR_ENGINE, DIR_GAMESTATE, "ComponentType.h");
                File.WriteAllText(componentTypePath, componentTypeString);
                Console.WriteLine("Wrote component types to: " + componentTypePath);
            }

            {
                string gameStateDataHelperPath = Path.Combine(DIR_SRC, DIR_ENGINE, DIR_GAMESTATE, "GameStateDataHelper.c");
                File.WriteAllText(gameStateDataHelperPath, gameStateDataHelperString);
                Console.WriteLine("Wrote game state data helper to: " + gameStateDataHelperPath);
            }

            Console.WriteLine("Completed creating component boiler plate!");
        }
        static void WriteTemplate(string fromPath, string toPath, string replaceForInclude, string replaceForResource, string replaceForResourceManager)
        {
            string contents = File.ReadAllText(fromPath);
            contents = contents.Replace(KEYWORD_INCLUDE_PATH, replaceForInclude);
            contents = contents.Replace(KEYWORD_RESOURCE, replaceForResource);
            contents = contents.Replace(KEYWORD_RESOURCE_LOWER, replaceForResource.ToLowerInvariant());
            contents = contents.Replace(KEYWORD_RESOURCE_MANAGER, replaceForResourceManager);
            File.WriteAllText(toPath, contents);
            Console.WriteLine("Generated boiler plate for " + toPath);
        }
        static void GenerateResourceBoilerPlate()
        {
            Console.WriteLine("Reading resource file");

            string pathForFileResource = Path.Combine(DIR_HELPER_RESOURCES, FILE_RESOURCE);
            if (!File.Exists(pathForFileResource))
            {
                Console.WriteLine("Unable to open resource file");
                return;
            }

            string[] resourceFileContents = File.ReadAllLines(pathForFileResource);
            foreach (string replaceResource in resourceFileContents)
            {
                string fileWithStruct = FindFileWithStruct(replaceResource);
                if (fileWithStruct == null)
                {
                    continue;
                }

                Console.WriteLine("Generating boiler plate for " + replaceResource);

                string replaceResourceManager = replaceResource + "Manager";

                string pathToRemoveFromFileWithStruct = Path.Combine(DIR_SRC, DIR_ENGINE);
                string replaceIncludePath = fileWithStruct.Replace(pathToRemoveFromFileWithStruct, "");
                replaceIncludePath = "../" + replaceIncludePath;
                replaceIncludePath = replaceIncludePath.Replace("\\", "/");
                replaceIncludePath = replaceIncludePath.Replace("//", "/");
                replaceIncludePath = "#include " + '"' + replaceIncludePath + '"';

                string resourceManagerPathForHeader = Path.Combine(DIR_SRC, DIR_ENGINE, DIR_RESOURCES, replaceResourceManager + ".h");
                WriteTemplate(Path.Combine(DIR_HELPER_RESOURCES, FILE_TEMPLATE_RESOURCE_HEADER),
                    resourceManagerPathForHeader, replaceIncludePath, replaceResource, replaceResourceManager);

                string resourceManagerPathForDefinition = Path.Combine(DIR_SRC, DIR_ENGINE, DIR_RESOURCES, replaceResourceManager + ".c");
                WriteTemplate(Path.Combine(DIR_HELPER_RESOURCES, FILE_TEMPLATE_RESOURCE_DEFINITIONS), 
                    resourceManagerPathForDefinition, replaceIncludePath, replaceResource, replaceResourceManager);
            }

            Console.WriteLine("Completed creating resource boiler plate!");
        }
        static string FindFileWithStructHelper(string path, string findThisStruct)
        {
            if (!Path.Exists(path))
            {
                Console.WriteLine("Unable to find " + path);
            }

            string[] files = Directory.GetFiles(path);
            foreach (string file in files)
            {
                string extension = Path.GetExtension(file);
                if (extension == ".c" || extension == ".h")
                {
                    string[] fileContents = File.ReadAllLines(file);
                    foreach (string fileContent in fileContents)
                    {
                        string trimmedFileContent = fileContent.Trim();
                        if (trimmedFileContent == findThisStruct)
                        {
                            return file;
                        }
                    }
                }
            }

            string[] directories = Directory.GetDirectories(path);
            foreach (string directory in directories)
            {
                string fileToReturn = FindFileWithStructHelper(directory, findThisStruct);
                if(fileToReturn != null)
                {
                    return fileToReturn;
                }
            }

            return null;
        }
        static string FindFileWithStruct(string findThisStruct)
        {
            string strToFind = "typedef struct " + findThisStruct;
            string path = Path.Combine(DIR_SRC);
            return FindFileWithStructHelper(path, strToFind);
        }
    }
}
