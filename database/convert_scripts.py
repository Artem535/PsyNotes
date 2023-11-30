# This Python file uses the following encoding: utf-8
from pathlib import Path
import argparse


def get_preamble() -> str:
    """
    This function returns a string that represents the preamble of an autogenerated file.
    
    Returns:
        str: The preamble string.
    """
    preamble = "//THIS FILE IS AUTOGENERATED.\n"
    preamble += "//It file was generated by $source_dir/database/convert_scripts.py\n"
    preamble += "#pragma once\n"
    return preamble

def format_sql_line(line: str) -> str:
    """
    Formats a single line of SQL code by replacing double quotes with escaped double quotes and replacing tabs with four spaces.
    Args:
        line (str): The line of SQL code to be formatted.
    Returns:
        str: The formatted line of SQL code.
    """
    spaces = " " * 4
    line = line.replace('"', '\\"')
    line = line.replace("\t", spaces)
    return f'{spaces}"{line} "\n'


def process_file(file: Path) -> str:
    """
    Generate a C++ variable declaration for a given SQL file.
    Args:
        file (Path): The path to the SQL file.
    Returns:
        str: The C++ variable declaration for the SQL file content.
    """
    sql: str = file.read_text(encoding="utf-8")
    sql_list = sql.split("\n")
    sql = "".join([format_sql_line(line) for line in sql_list])
    variable = f"constexpr char {file.stem}[] = \n{sql}"[:-1] + ";"
    return variable


def format_result_str(variables: str) -> str:
    """
    Formats the result string by combining the given variables with the start and end namespaces.
    Args:
        variables (str): The variables to be included in the result string.
    Returns:
        str: The formatted result string.
    """
    start_namespace = "namespace constants {\nnamespace sql{\n"
    end_namespace = "\n}; // namespace sql\n}; // namespace constants"
    return get_preamble() + start_namespace + variables + end_namespace


def format_results(input_dir: Path) -> str:
    """
    Generate a formatted string of results based on the input directory.
    
    Args:
        input_dir (Path): The directory containing the SQL files.
        
    Returns:
        str: The formatted string of results.
    """
    files = input_dir.glob("*.sql")
    variables = "\n".join([process_file(file) for file in files])
    return format_result_str(variables)


def main() -> None:
    parser = argparse.ArgumentParser("Convert SQL scripts to constexpr C++ strings.")
    parser.add_argument("input_dir", help="Input directory where placed sql scripts.")
    parser.add_argument("output_file", help="Output file to write to.")
    args = parser.parse_args()

    results = format_results(Path(args.input_dir))
    output_file = Path(args.output_file)
    output_file.write_text(results, encoding="utf-8")


if __name__ == "__main__":
    main()
