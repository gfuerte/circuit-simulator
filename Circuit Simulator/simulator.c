#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>

int** createTable(int rows, int cols, int inputVar) {
	int** table = malloc(rows*sizeof(int*));

	for(int i = 0; i < rows; i++) {
		table[i] = malloc(cols*sizeof(int));
	}

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			table[i][j] = -1;
		}
	}

	int numZeroes = 1;
	int pattern = 2;
	for(int j = inputVar-1; j >= 0; j--) {
		
		int index = 0;
		for(int i = 0; i < numZeroes; i++) {
			table[index][j] = 0;
			index++;
		}

		bool check = true;
		while(check) {
			for(int i = 0; i < pattern; i++) {
				table[index][j] = 1;
				index++;
				if(index == rows) {
					check = false;
					break;
				}
			}
			if(!check) {
				break;
			}

			for(int i = 0; i < pattern; i++) {
				table[index][j] = 0;
				index++;
				if(index == rows) {
					check = false;
					break;
				}
			}
			if(!check) {
				break;
			}
		}
		
		numZeroes *= 2;
		pattern *= 2;
		index = 0;
	}

	return table;	
}

int** createGray(int rows, int cols) {
	int** table = malloc(rows*sizeof(int*));

	for(int i = 0; i < rows; i++) {
		table[i] = malloc(cols*sizeof(int));
	}

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			table[i][j] = -1;
		}
	}

	int numZeroes = 1;
	int pattern = 2;
	for(int j = cols-1; j >= 0; j--) {
		
		int index = 0;
		for(int i = 0; i < numZeroes; i++) {
			table[index][j] = 0;
			index++;
		}

		bool check = true;
		while(check) {
			for(int i = 0; i < pattern; i++) {
				table[index][j] = 1;
				index++;
				if(index == rows) {
					check = false;
					break;
				}
			}
			if(!check) {
				break;
			}

			for(int i = 0; i < pattern; i++) {
				table[index][j] = 0;
				index++;
				if(index == rows) {
					check = false;
					break;
				}
			}
			if(!check) {
				break;
			}
		}
		
		numZeroes *= 2;
		pattern *= 2;
		index = 0;
	}

	return table;	
}

bool isNumber(char c) {
	if(c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9') {
		return true;
	}
	return false;
}

void separate(char* var) {
	for(int i = 0; i < strlen(var); i++) {
		if(isNumber(var[i]) == true) {
			var[i] = '\0';
			break;
		}
	}
}

int getIndex(char* var) {
	int result = 0;
	char var_indexArr[21] = "";
	int num_index = 0;
	for(int i = 0; i < strlen(var); i++) {
		if(isNumber(var[i]) == true) {
			var_indexArr[num_index] = var[i];
			num_index++;
		}
	}
	result = atoi(var_indexArr);
	return result;
}

void print_table(int** table, int rows, int cols) {
	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++) {
			printf("%d ", table[i][j]);
		}
		printf("\n");
	}
}

void free_table(int** table, int rows) {
	for (int i = 0; i < rows; i++) {
		free(table[i]);
	}
	free(table);
}

int main(int argc, char** argv) {
	if(argc != 2) {
		printf("insufficient arguements\n");
		exit(0);
	}

	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL) {
		printf("error\n");
		exit(0);
	}

	char* cur = malloc(sizeof(char)*20);
	int inputVar;
	int outputVar;
	char inputVarName[21] = "";
	char outputVarName[21] = "";
	char tempVarName[21] = "";
	bool once = true;
	while(fscanf(fp, "%s", cur) != EOF) {
		if(strcmp(cur, "INPUTVAR") == 0) {
			fscanf(fp, " %d", &inputVar);
			fscanf(fp, " %s", inputVarName);
			separate(inputVarName);
		}
		if(strcmp(cur, "OUTPUTVAR") == 0) {
			fscanf(fp, " %d", &outputVar);
			fscanf(fp, " %s", outputVarName);
			separate(outputVarName);
		}
		if(once) {
			if(strcmp(cur, "NOT") == 0 || strcmp(cur, "AND") == 0 || strcmp(cur, "OR") == 0 || strcmp(cur, "NAND") == 0
				       	|| strcmp(cur, "NOR") == 0 || strcmp(cur, "XOR") == 0 || strcmp(cur, "XNOR") == 0) {
				fscanf(fp, " %s", tempVarName);
				separate(tempVarName);

				if(strcmp(tempVarName, inputVarName) != 0 && strcmp(tempVarName, outputVarName) != 0 && strcmp(tempVarName, "") != 0) {
					once = false;
					continue;
				}	

				fscanf(fp, " %s", tempVarName);
				separate(tempVarName);

				if(strcmp(tempVarName, inputVarName) != 0 && strcmp(tempVarName, outputVarName) != 0 && strcmp(tempVarName, "") != 0) {
					once = false;
					continue;
				}	
			} else if(strcmp(cur, "DECODER") == 0) {
				int counter;
				fscanf(fp, " %d", &counter);
				int add_on = 1;
				for(int i = 0; i < counter; i++) {
					add_on *= 2;
				}
				for(int i = 0; i < (counter + add_on); i++) {
					fscanf(fp, " %s", tempVarName);
					separate(tempVarName);
					if(strcmp(tempVarName, inputVarName) != 0 && strcmp(tempVarName, outputVarName) != 0 && strcmp(tempVarName, "") != 0) {
						once = false;
						break;
					}	
				}
				if(!once) { continue; };
			} else if(strcmp(cur, "MULTIPLEXER") == 0) {
				int counter;
				fscanf(fp, " %d", &counter);
				int add_on = log2(counter);
				for(int i = 0; i < (counter + add_on); i++) {
					fscanf(fp, " %s", tempVarName);
					separate(tempVarName);
					if(strcmp(tempVarName, inputVarName) != 0 && strcmp(tempVarName, outputVarName) != 0 && strcmp(tempVarName, "") != 0) {
						once = false;
						break;
					}	
				}
				if(!once) { continue; };
			}
		}			
	}
	fclose(fp);
	free(cur);

	int rows = 1;
	int cols = inputVar + outputVar;
	for(int i = 0; i < inputVar; i++) {
		rows *= 2;
	}

	int** table = createTable(rows, cols, inputVar);
	
	char* temp = malloc(sizeof(char)*20);
	for(int curGray = 0; curGray < rows; curGray++) {
		int tempVarArr[100] = { 0 };
		for(int i = 0; i < 100; i++) {
			tempVarArr[i] = -1;
		}
		bool loop = true;
		while(loop) {
			FILE* file = fopen(argv[1], "r");
			while(fscanf(file, "%s", temp) != EOF) {
				if(strcmp(temp, "NOT") == 0) {
					int result = 0;
					char var[21] = "";
					char output[21] = "";

					fscanf(file, " %s", var);
					fscanf(file, " %s", output);

					int output_index = getIndex(output);
					separate(output);
					
					bool possible = true;
					if(strcmp(var, "0") == 0) {
						result = 0;	
					} else if (strcmp(var, "1") == 0) {
						result = 1;
					} else {
						int var_index = getIndex(var);
						separate(var);
						if(strcmp(var, inputVarName) == 0) {
							result = table[curGray][var_index-1];
						       	if(result == 0) {
								result = 1;
							} else {
								result = 0;
							}	
						} else if(strcmp(var, tempVarName) == 0) {
							if(tempVarArr[var_index] == -1) {
								possible = false;
							} else {
								result = tempVarArr[var_index];
								if(result == 0) {
									result = 1;
								} else {
									result = 0;
								}
							}
						}
					}
					if(possible) {
						if(strcmp(output, outputVarName) == 0){
							table[curGray][inputVar+output_index-1] = result;
						} else if(strcmp(output, tempVarName) == 0) {
							tempVarArr[output_index] = result;
						}
					} else {
						continue;
					}
				} else if(strcmp(temp, "AND") == 0) {
					int result = 0;
					char var1[21] = "";
					char var2[21] = "";
					char output[21] = "";

					fscanf(file, " %s", var1);
					fscanf(file, " %s", var2);
					fscanf(file, " %s", output);

					int output_index = getIndex(output);
					separate(output);
					
					bool possible = true;
					if(strcmp(var1, "0") == 0 || strcmp(var2, "0") == 0) {
						result = 0;	
					} else if (strcmp(var1, "1") == 0 && strcmp(var2, "1") == 0) {
						result = 1;
					} else {
						int var1_index = getIndex(var1);
						int var2_index = getIndex(var2);
						int var1_value = 0;
						int var2_value = 0;
						if(strcmp(var1, "1") == 0) {
							var1_value = 1;
						}
						if(strcmp(var2, "1") == 0) {
							var2_value = 1;
						}
						separate(var1);
						separate(var2);
						if(strcmp(var1, inputVarName) == 0) {
							var1_value = table[curGray][var1_index-1];
						} else if(strcmp(var1, tempVarName) == 0) {
							if(tempVarArr[var1_index] == -1) {
								possible = false;
							} else {
								var1_value = tempVarArr[var1_index];
							}
						}
						if(strcmp(var2, inputVarName) == 0) {
							var2_value = table[curGray][var2_index-1];
						} else if(strcmp(var2, tempVarName) == 0) {
							if(tempVarArr[var2_index] == -1) {
								possible = false;
							} else {
								var2_value = tempVarArr[var2_index];
							}
						}
						if(var1_value == 1 && var2_value == 1) {
							result = 1;
						} else {
							result = 0;
						}
					}
					if(possible) {
						if(strcmp(output, outputVarName) == 0){
							table[curGray][inputVar+output_index-1] = result;
						} else if(strcmp(output, tempVarName) == 0) {
							tempVarArr[output_index] = result;
						}
					} else {
						continue;
					}
				} else if(strcmp(temp, "OR") == 0) {
					int result = 0;
					char var1[21] = "";
					char var2[21] = "";
					char output[21] = "";

					fscanf(file, " %s", var1);
					fscanf(file, " %s", var2);
					fscanf(file, " %s", output);

					int output_index = getIndex(output);
					separate(output);
					
					bool possible = true;
					if(strcmp(var1, "1") == 0 || strcmp(var2, "1") == 0) {
						result = 1;	
					} else if (strcmp(var1, "0") == 0 && strcmp(var2, "0") == 0) {
						result = 0;
					} else {
						int var1_index = getIndex(var1);
						int var2_index = getIndex(var2);
						int var1_value = 0;
						int var2_value = 0;
						if(strcmp(var1, "1") == 0) {
							var1_value = 1;
						}
						if(strcmp(var2, "1") == 0) {
							var2_value = 1;
						}
						separate(var1);
						separate(var2);
						if(strcmp(var1, inputVarName) == 0) {
							var1_value = table[curGray][var1_index-1];
						} else if(strcmp(var1, tempVarName) == 0) {
							if(tempVarArr[var1_index] == -1) {
								possible = false;
							} else {
								var1_value = tempVarArr[var1_index];
							}
						}
						if(strcmp(var2, inputVarName) == 0) {
							var2_value = table[curGray][var2_index-1];
						} else if(strcmp(var2, tempVarName) == 0) {
							if(tempVarArr[var2_index] == -1) {
								possible = false;
							} else {
								var2_value = tempVarArr[var2_index];
							}
						}
						if(var1_value == 1 || var2_value == 1) {
							result = 1;
						} else {
							result = 0;
						}
					}
					if(possible) {
						if(strcmp(output, outputVarName) == 0){
							table[curGray][inputVar+output_index-1] = result;
						} else if(strcmp(output, tempVarName) == 0) {
							tempVarArr[output_index] = result;
						}
					} else {
						continue;
					}
				
				} else if(strcmp(temp, "NAND") == 0) {
					int result = 0;
					char var1[21] = "";
					char var2[21] = "";
					char output[21] = "";

					fscanf(file, " %s", var1);
					fscanf(file, " %s", var2);
					fscanf(file, " %s", output);

					int output_index = getIndex(output);
					separate(output);
					
					bool possible = true;
					if(strcmp(var1, "0") == 0 || strcmp(var2, "0") == 0) {
						result = 1;	
					} else if (strcmp(var1, "1") == 0 && strcmp(var2, "1") == 0) {
						result = 0;
					} else {
						int var1_index = getIndex(var1);
						int var2_index = getIndex(var2);
						int var1_value = 0;
						int var2_value = 0;
						if(strcmp(var1, "1") == 0) {
							var1_value = 1;
						}
						if(strcmp(var2, "1") == 0) {
							var2_value = 1;
						}
						separate(var1);
						separate(var2);
						if(strcmp(var1, inputVarName) == 0) {
							var1_value = table[curGray][var1_index-1];
						} else if(strcmp(var1, tempVarName) == 0) {
							if(tempVarArr[var1_index] == -1) {
								possible = false;
							} else {
								var1_value = tempVarArr[var1_index];
							}
						}
						if(strcmp(var2, inputVarName) == 0) {
							var2_value = table[curGray][var2_index-1];
						} else if(strcmp(var2, tempVarName) == 0) {
							if(tempVarArr[var2_index] == -1) {
								possible = false;
							} else {
								var2_value = tempVarArr[var2_index];
							}
						}
						if(var1_value == 1 && var2_value == 1) {
							result = 0;
						} else {
							result = 1;
						}
					}
					if(possible) {
						if(strcmp(output, outputVarName) == 0){
							table[curGray][inputVar+output_index-1] = result;
						} else if(strcmp(output, tempVarName) == 0) {
							tempVarArr[output_index] = result;
						}
					} else {
						continue;
					}
				
				} else if(strcmp(temp, "NOR") == 0) {
					int result = 0;
					char var1[21] = "";
					char var2[21] = "";
					char output[21] = "";

					fscanf(file, " %s", var1);
					fscanf(file, " %s", var2);
					fscanf(file, " %s", output);

					int output_index = getIndex(output);
					separate(output);
					
					bool possible = true;
					if(strcmp(var1, "1") == 0 || strcmp(var2, "1") == 0) {
						result = 0;	
					} else if (strcmp(var1, "0") == 0 && strcmp(var2, "0") == 0) {
						result = 1;
					} else {
						int var1_index = getIndex(var1);
						int var2_index = getIndex(var2);
						int var1_value = 0;
						int var2_value = 0;
						if(strcmp(var1, "1") == 0) {
							var1_value = 1;
						}
						if(strcmp(var2, "1") == 0) {
							var2_value = 1;
						}
						separate(var1);
						separate(var2);
						if(strcmp(var1, inputVarName) == 0) {
							var1_value = table[curGray][var1_index-1];
						} else if(strcmp(var1, tempVarName) == 0) {
							if(tempVarArr[var1_index] == -1) {
								possible = false;
							} else {
								var1_value = tempVarArr[var1_index];
							}
						}
						if(strcmp(var2, inputVarName) == 0) {
							var2_value = table[curGray][var2_index-1];
						} else if(strcmp(var2, tempVarName) == 0) {
							if(tempVarArr[var2_index] == -1) {
								possible = false;
							} else {
								var2_value = tempVarArr[var2_index];
							}
						}
						if(var1_value == 1 || var2_value == 1) {
							result = 0;
						} else {
							result = 1;
						}
					}
					if(possible) {
						if(strcmp(output, outputVarName) == 0){
							table[curGray][inputVar+output_index-1] = result;
						} else if(strcmp(output, tempVarName) == 0) {
							tempVarArr[output_index] = result;
						}
					} else {
						continue;
					}
				} else if(strcmp(temp, "XOR") == 0) {
					int result = 0;
					char var1[21] = "";
					char var2[21] = "";
					char output[21] = "";

					fscanf(file, " %s", var1);
					fscanf(file, " %s", var2);
					fscanf(file, " %s", output);

					int output_index = getIndex(output);
					separate(output);
					
					bool possible = true;
					if((strcmp(var1, "1") == 0 && strcmp(var2, "1") == 0) || (strcmp(var1, "0") == 0 && strcmp(var2, "0") == 0))  {
						result = 0;	
					} if((strcmp(var1, "1") == 0 && strcmp(var2, "0") == 0) || (strcmp(var1, "0") == 0 && strcmp(var2, "1") == 0))  {
						result = 1;
					} else {
						int var1_index = getIndex(var1);
						int var2_index = getIndex(var2);
						int var1_value = 0;
						int var2_value = 0;
						if(strcmp(var1, "1") == 0) {
							var1_value = 1;
						}
						if(strcmp(var2, "1") == 0) {
							var2_value = 1;
						}
						separate(var1);
						separate(var2);
						if(strcmp(var1, inputVarName) == 0) {
							var1_value = table[curGray][var1_index-1];
						} else if(strcmp(var1, tempVarName) == 0) {
							if(tempVarArr[var1_index] == -1) {
								possible = false;
							} else {
								var1_value = tempVarArr[var1_index];
							}
						}
						if(strcmp(var2, inputVarName) == 0) {
							var2_value = table[curGray][var2_index-1];
						} else if(strcmp(var2, tempVarName) == 0) {
							if(tempVarArr[var2_index] == -1) {
								possible = false;
							} else {
								var2_value = tempVarArr[var2_index];
							}
						}
						if((var1_value == 1 && var2_value == 1) || (var1_value == 0 && var2_value == 0)) {
							result = 0;
						} else {
							result = 1;
						}
					}
					if(possible) {
						if(strcmp(output, outputVarName) == 0){
							table[curGray][inputVar+output_index-1] = result;
						} else if(strcmp(output, tempVarName) == 0) {
							tempVarArr[output_index] = result;
						}
					} else {
						continue;
					}
				} else if(strcmp(temp, "XNOR") == 0) {
					int result = 0;
					char var1[21] = "";
					char var2[21] = "";
					char output[21] = "";

					fscanf(file, " %s", var1);
					fscanf(file, " %s", var2);
					fscanf(file, " %s", output);

					int output_index = getIndex(output);
					separate(output);
					
					bool possible = true;
					if((strcmp(var1, "1") == 0 && strcmp(var2, "1") == 0) || (strcmp(var1, "0") == 0 && strcmp(var2, "0") == 0))  {
						result = 1;	
					} if((strcmp(var1, "1") == 0 && strcmp(var2, "0") == 0) || (strcmp(var1, "0") == 0 && strcmp(var2, "1") == 0))  {
						result = 0;
					} else {
						int var1_index = getIndex(var1);
						int var2_index = getIndex(var2);
						int var1_value = 0;
						int var2_value = 0;
						if(strcmp(var1, "1") == 0) {
							var1_value = 1;
						}
						if(strcmp(var2, "1") == 0) {
							var2_value = 1;
						}
						separate(var1);
						separate(var2);
						if(strcmp(var1, inputVarName) == 0) {
							var1_value = table[curGray][var1_index-1];
						} else if(strcmp(var1, tempVarName) == 0) {
							if(tempVarArr[var1_index] == -1) {
								possible = false;
							} else {
								var1_value = tempVarArr[var1_index];
							}
						}
						if(strcmp(var2, inputVarName) == 0) {
							var2_value = table[curGray][var2_index-1];
						} else if(strcmp(var2, tempVarName) == 0) {
							if(tempVarArr[var2_index] == -1) {
								possible = false;
							} else {
								var2_value = tempVarArr[var2_index];
							}
						}
						if((var1_value == 1 && var2_value == 1) || (var1_value == 0 && var2_value == 0)) {
							result = 1;
						} else {
							result = 0;
						}
					}
					if(possible) {
						if(strcmp(output, outputVarName) == 0){
							table[curGray][inputVar+output_index-1] = result;
						} else if(strcmp(output, tempVarName) == 0) {
							tempVarArr[output_index] = result;
						}
					} else {
						continue;
					}
				} else if(strcmp(temp, "DECODER") == 0) {
					int decode_num;
					fscanf(file, " %d", &decode_num);
					int input_count = decode_num;
					int output_count = 1;
					for(int i = 0; i < input_count; i++) {
						output_count *= 2;
					}
					int** grayTable = createGray(output_count, input_count);
					int inputArr[100] = { 0 };
					bool possible = true;
					for(int i = 0; i < input_count; i++) {
						int var_value = -1;
						char var[21] = "";
						fscanf(file, " %s", var);
						
						if((strcmp(var, "1") == 0))  {
							var_value = 1;	
						} if((strcmp(var, "0") == 0))  {
							var_value = 0;
						} else {
							int var_index = getIndex(var);
							separate(var);
							if(strcmp(var, inputVarName) == 0) {
								var_value = table[curGray][var_index-1];
							} else if(strcmp(var, tempVarName) == 0) {
								if(tempVarArr[var_index] == -1) {
									possible = false;
									break;
								} else {
									var_value = tempVarArr[var_index];
								}
							}
						}
						inputArr[i] = var_value;	
					}
					if(possible) {
						for(int i = 0; i < output_count; i++) {
							int copy[100] = { 0 };
							for(int j = 0; j < input_count; j++) {
								copy[j] = inputArr[j];
							}
							int result = 1;
							for(int j = 0; j < input_count; j++) {
								if(grayTable[i][j] == 0) {
									if(copy[j] == 1) {
										copy[j] = 0;
									} else if(copy[j] == 0) {
										copy[j] = 1;
									}
								}
								if(copy[j] == 0) {
									result = 0;
									break;
								}
							}
							char output[21] = "";
							fscanf(file, " %s", output);
							int output_index = getIndex(output);
							separate(output);

							if(strcmp(output, outputVarName) == 0){
								table[curGray][inputVar+output_index-1] = result;
							} else if(strcmp(output, tempVarName) == 0) {
								tempVarArr[output_index] = result;
							}
						}
					} else {
						continue;
					}
					free_table(grayTable, output_count);
				} else if(strcmp(temp, "MULTIPLEXER") == 0) {
					int multi_rows;
					int multi_cols;
					fscanf(file, " %d", &multi_rows);
					multi_cols = log2(multi_rows);

					int** grayTable = createGray(multi_rows, multi_cols);

					bool possible = true;
					int values[100] = { 0 };
					for(int i = 0; i < multi_rows; i++) {
						int var_value; 
						char var[21] = "";
						fscanf(file, " %s", var);
						if(strcmp(var, "1") == 0) {
							var_value = 1;	
						} else if (strcmp(var, "0") == 0) {
							var_value = 0;
						} else {
							int var_index = getIndex(var);
							separate(var);
							if(strcmp(var, inputVarName) == 0) {
								var_value = table[curGray][var_index-1];
							} else if(strcmp(var, tempVarName) == 0) {
								if(tempVarArr[var_index] == -1) {
									possible = false;
								} else {
									var_value = tempVarArr[var_index];
								}
							}
						}
						values[i] = var_value;
					}
					int select[100] = { 0 };
					for(int i = 0; i < multi_cols; i++) {
						int select_value; 
						char sel[21] = "";
						fscanf(file, " %s", sel);
						if(strcmp(sel, "1") == 0) {
							select_value = 1;	
						} else if (strcmp(sel, "0") == 0) {
							select_value = 0;
						} else {
							int select_index = getIndex(sel);
							separate(sel);
							if(strcmp(sel, inputVarName) == 0) {
								select_value = table[curGray][select_index-1];
							} else if(strcmp(sel, tempVarName) == 0) {
								if(tempVarArr[select_index] == -1) {
									possible = false;
								} else {
									select_value = tempVarArr[select_index];
								}
							}
						}
						select[i] = select_value;
					}
					if(possible) {
						int multi_index;
						for(int i = 0; i < multi_rows; i++) {
							for(int j = 0; j < multi_cols; j++) {
								if(grayTable[i][j] != select[j]) {
									break;
								}
								if(j == multi_cols-1) {
									multi_index = i;
									i = rows;
									break;
								}
							}
						}
						int result;
						result = values[multi_index];
						char output[21] = "";
						fscanf(file, " %s", output);
						int output_index = getIndex(output);
						separate(output);
						if(strcmp(output, outputVarName) == 0){
							table[curGray][inputVar+output_index-1] = result;
						} else if(strcmp(output, tempVarName) == 0) {
							tempVarArr[output_index] = result;
						}
					} else {
						continue;
					}
					free_table(grayTable, multi_rows);
				}
			}
			bool done = true;
			for(int i = inputVar; i < cols; i++) {
				if(table[curGray][i] == -1) {;
					done = false;
					break;
				}
			}
			if(done) {
				loop = false;
			}
			fclose(file);
		}
	}
	free(temp);
	print_table(table, rows, cols);
	free_table(table, rows);
	return 0;
}

