using System;
using System.Diagnostics;
using System.IO;
using System.Threading;

namespace AutoBuild
{
	public class BuildFirmware
	{
		private static readonly string hexFile = "Marlin.ino.hex";
		private static readonly string hexPath = "Build";
		private static readonly string settingsFile = "Configuration_Pulse.h";
		private static readonly string sourcePath = "\\Development\\PulseV1Firmware\\Marlin";
		private static readonly string sourceIno = "Marlin.ino";
		private static readonly string arduinoPath = "\\Program Files (x86)\\Arduino";
		private static readonly string arduinoExe = "arduino.exe";

		private int BedType;
		private int ControllerType;
		private int ExtruderType;

		public BuildFirmware(int bedType, int controllerType, int extruderType)
		{
			this.BedType = bedType;
			this.ControllerType = controllerType;
			this.ExtruderType = extruderType;

			Console.WriteLine("");
			Directory.SetCurrentDirectory(sourcePath);
			Console.WriteLine($"Current Directory = {Directory.GetCurrentDirectory()}");
			SetConfigFile();
			CleanBuildDirectory();
			RunBuild();
			RenameBuildResults();
		}

		private void RenameBuildResults()
		{
			var timer = Stopwatch.StartNew();
			var pathAndFile = Path.Combine(hexPath, hexFile);
			while (timer.Elapsed.TotalMinutes < 2
				&& !File.Exists(pathAndFile))
			{
				// wait for the results file
				Thread.Sleep(500);
			}

			Console.WriteLine();

			if (File.Exists(pathAndFile))
			{
				// wait to make sure the file is closed
				Thread.Sleep(500);
				var destFile = Path.Combine(hexPath, "..", $"C{BedType}{ControllerType}{ExtruderType}.hex");
				if(File.Exists(destFile))
				{
					File.Delete(destFile);
				}
				File.Move(pathAndFile, destFile);
				Console.WriteLine($"Done {BedType}{ControllerType}{ExtruderType}");
			}
			else
			{
				Console.WriteLine($"Failed {BedType}{ControllerType}{ExtruderType}");
			}

			Thread.Sleep(1000);
		}

		private void CleanBuildDirectory()
		{
			var timer = Stopwatch.StartNew();
			var pathAndFile = Path.Combine(hexPath, hexFile);
			while(Directory.Exists(hexPath)
				&& timer.Elapsed.TotalSeconds < 30)
			{
				try
				{
					Directory.Delete(hexPath, true);
				}
				catch
				{

				}
				Thread.Sleep(1000);
			}

			Directory.CreateDirectory(hexPath);
		}

		void RunBuild()
		{
			var arduinoPathAndFile = Path.Combine(arduinoPath, arduinoExe);
			string commandArgs = $"--pref build.path={hexPath} --verify {sourceIno}";

			Console.WriteLine($"Runnig arduino and building...");
			Console.WriteLine($"\"{arduinoPathAndFile}\" {commandArgs}");

			var buildProcess = new Process()
			{
				StartInfo = new ProcessStartInfo()
				{
					Arguments = commandArgs,
					//CreateNoWindow = true,
					//WindowStyle = ProcessWindowStyle.Hidden,
					//RedirectStandardError = true,
					//RedirectStandardOutput = true,
					FileName = arduinoPathAndFile,
					//UseShellExecute = false
				}
			};

			buildProcess.Start();

			buildProcess.WaitForExit();
		}

		private void FindLineAndSetValue(string[] lines, string find, int value)
		{
			for(int i=0; i<lines.Length; i++)
			{
				if(lines[i].StartsWith(find))
				{
					lines[i] = $"{find} {value}";
					break;
				}
			}
		}

		private void SetConfigFile()
		{
			Console.WriteLine($"Modifying {settingsFile} to {BedType}{ControllerType}{ExtruderType}...");

			var settingsPathAndFile = Path.Combine(sourcePath, settingsFile);
			var lines = File.ReadAllLines(settingsPathAndFile);

			// find and replace the lines
			FindLineAndSetValue(lines, "#define BedType", BedType);
			FindLineAndSetValue(lines, "#define ControllerType", ControllerType);
			FindLineAndSetValue(lines, "#define ExtruderType", ExtruderType);

			File.WriteAllLines(settingsPathAndFile, lines);
		}
	}

	internal class Program
	{
		private static readonly string[] activeFirmware = new string[]
		{
			// big bed with level sensor & new tall frame
			"111", "112", "113",
			"121", "122", "123",
			//"131", "132", "133",
			"231", "232", "233",
		};

		private static void GetOption(string typeDescription, string[] options, ref int selection, int startingIndex)
		{
			while (selection < startingIndex
				|| selection >= options.Length + startingIndex)
			{
				Console.WriteLine();

				for (int i = 0; i < options.Length; i++)
				{
					Console.WriteLine($"{i + startingIndex} = {options[i]}");
				}

				Console.Write(typeDescription + " ");

				var input = Console.ReadLine();
				if (!int.TryParse(input, out selection)
					|| selection < startingIndex
					|| selection >= options.Length + startingIndex)
				{
					Console.WriteLine($"INVALID INPUT: ({input})");
					selection = -1;
				}
			}
		}

		private static void Main(string[] args)
		{
			int buildAll = -1;
			string[] buildOptions = new string[] { "All", "Single" };
			GetOption("What to Build:", buildOptions, ref buildAll, 0);

			if (buildAll == 0)
			{
				foreach (var model in activeFirmware)
				{
					var builder = new BuildFirmware(int.Parse(model.Substring(0, 1)),
						int.Parse(model.Substring(1, 1)),
						int.Parse(model.Substring(2, 1)));
				}
			}
			else
			{
				// First Digit (Bed & Leveling)
				// 1 = Heated, Probe
				int bedType = -1;
				string[] bedOptions = new string[] { "Heated, Probe" };
				GetOption("Select Bed Type:", bedOptions, ref bedType, 1);

				// Second Digit (Electronics)
				// 1 = No LCD, 2 = LCD, 3 = Viki
				int electronicsType = -1;
				string[] electronicsOptions = new string[] { "No LCD", "LCD", "Viki" };
				GetOption("Select Electronics Type:", electronicsOptions, ref electronicsType, 1);

				// Third Digit (Hotend & Extruder)
				// 1 = EZ-Struder & E3D light, 2 = BondTech & E3Dv6, 3 = 3mm BondTech & 3mm E3Dv6
				int hotendExtruderType = -1;
				string[] hotendExtruderOptions = new string[] { "EZ-Struder & E3D light", "BondTech & E3Dv6", "3mm BondTech & 3mm E3Dv6" };
				GetOption("Select Hotend and Extruder Type:", hotendExtruderOptions, ref hotendExtruderType, 1);

				var builder = new BuildFirmware(bedType, electronicsType, hotendExtruderType);
			}
		}
	}
}