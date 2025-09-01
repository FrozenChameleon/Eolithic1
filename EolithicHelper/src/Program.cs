/* EolithicEngine
 * Copyright 2025 Patrick Derosby
 * Released under the zlib License.
 * See LICENSE for details.
 */

namespace EolithicHelper
{
    class Program
    {
        private const string FILE_RESOURCE = "resources.txt";
        private const string FILE_TEMPLATE_RESOURCE_HEADER = "Template_RESOURCE.h";
        private const string FILE_TEMPLATE_RESOURCE_DEFINITIONS = "Template_RESOURCE.c";
        private const string DIR_HELPER_RESOURCES = "helper_resources";
        private const string DIR_SRC = "src";
        private const string DIR_ENGINE = "engine";
        private const string DIR_RESOURCES = "resources";
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
            Console.WriteLine("[A] - Generate Resource Boilerplate From " + FILE_RESOURCE);
            Console.WriteLine("[P] - Exit");

            Loop();
        }
        static void Loop()
        {
            while (true)
            {
                if(!Console.KeyAvailable)
                {
                    continue;
                }

                ConsoleKey key = Console.ReadKey().Key;
                if (key == ConsoleKey.A)
                {
                    GenerateResourceBoilerPlate();
                }
                else if (key == ConsoleKey.P)
                {
                    Environment.Exit(0);
                }
            }
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
