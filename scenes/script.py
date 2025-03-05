def remove_dash_from_lines(input_file, output_file):
    with open(input_file, 'r') as infile, open(output_file, 'w') as outfile:
        for line in infile:
            # Remove the dash at the end of the line and any trailing whitespace
            cleaned_line = line.rstrip().rstrip('-').rstrip()
            outfile.write(cleaned_line + '\n')

# Example usage
input_file = 'file.rt'
output_file = 'file_cleaned.rt'
remove_dash_from_lines(input_file, output_file)
print(f"Processed file saved as {output_file}")
