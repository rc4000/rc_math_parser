#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

void imprimir_elementos(vector<string> vec){

	cout << "========================" << endl;
	for(int i =0;i<vec.size();i++){
		cout << "(" <<  i << ")" << " : [" << vec[i] << "]" << endl;
	}cout << "========================" << endl;

}





bool es_una_operacion(char caracter){

    if(caracter=='+' or caracter=='-' or caracter=='/' or caracter=='*' or caracter=='(' or caracter==')'){
        return true;
    }else{
        return false;
    }


}


string x_caracteres_despues_de_i(int i,int x,string cdn){

		string cdn_resul = "";

		for(int e=i; e<i+x;e++){
			cdn_resul = cdn_resul + cdn[e];
		}
		
	
		return cdn_resul;
}





string replace_with(string cadena,string buscar,string cambiar){

	string string_a_retornar = "";


	for(int i=0;i<cadena.length();i++){

		if(x_caracteres_despues_de_i(i,buscar.length(),cadena) == buscar ){

			string_a_retornar = string_a_retornar + cambiar;
			i = i + buscar.length() -1 ;
			
		}else{

			string_a_retornar = string_a_retornar + cadena[i];

		}


	}


	return string_a_retornar;

}





vector<string> separar_por_operacion(string exp){

	vector<string> resultado;

	string data_a_cargar = "";
	bool signo_cargado = false;


	exp = replace_with(exp,"div","|");
	exp = replace_with(exp,"mod","%");
	exp = replace_with(exp,"pow","^");
	exp = replace_with(exp,"**","^");
	exp = replace_with(exp,"--","+");
	exp = replace_with(exp,"+-","-");
	exp = replace_with(exp,"-+","-");




	for(int i=0;i<exp.length();i++){

		if(exp[i]=='+' or exp[i]=='-'){


				if(signo_cargado==false){

					data_a_cargar = data_a_cargar + exp[i];
					signo_cargado=true;

				}else{
					resultado.push_back(data_a_cargar);
					data_a_cargar = "";
					data_a_cargar = data_a_cargar + exp[i];

				}


		}else{



				if(exp[i]=='*' or exp[i]=='/' or exp[i]=='|' or exp[i]=='%' or exp[i]=='^' or exp[i]=='(' or exp[i]==')' ){

					if(data_a_cargar.length()!=0){
						resultado.push_back(data_a_cargar);
					}
					data_a_cargar = "";
					data_a_cargar = data_a_cargar + exp[i];
					resultado.push_back(data_a_cargar);
					signo_cargado = false;
					data_a_cargar = "";

				}else{


					if(signo_cargado==false){
						data_a_cargar = data_a_cargar + "+";
						signo_cargado=true;
					}


					data_a_cargar = data_a_cargar + exp[i];


				}


		}
           

	}

	if(data_a_cargar.length()!=0){
		resultado.push_back(data_a_cargar);
	}

	//imprimir_elementos(resultado);

	return resultado;
}


bool hay_parentesis(vector<string> data){

	for(int i=0;i<data.size();i++){

		if(data[i][0]=='(' or data[i][0]==')'){
			return true;
		}

	}

	return false;
}


bool hay_productos(vector<string> data){

	for(int i=0;i<data.size();i++){

		if(data[i][0]=='*'){
			return true;
		}

	}

	return false;
}

bool hay_divisiones(vector<string> data){

	for(int i=0;i<data.size();i++){

		if(data[i][0]=='/'){
			return true;
		}

	}

	return false;
}

bool hay_divs(vector<string> data){

	for(int i=0;i<data.size();i++){

		if(data[i][0]=='|'){
			return true;
		}

	}

	return false;
}

bool hay_mods(vector<string> data){

	for(int i=0;i<data.size();i++){

		if(data[i][0]=='%'){
			return true;
		}

	}

	return false;
}

bool hay_pows(vector<string> data){

	for(int i=0;i<data.size();i++){

		if(data[i][0]=='^'){
			return true;
		}

	}

	return false;
}




vector<string> resolver_productos(vector<string> exp_vec){

	vector<string> nuevo_exp_vec;

	float resultado = 0;

	string aux_exp = "";
	float num1 = 0;
	float num2 = 0;

	if(hay_productos(exp_vec)){
		for(int i=0;i<exp_vec.size();i++){


			if(exp_vec.size()>i+1){

				if(exp_vec[i + 1][0] == '*'){

					//calcular num1

					for(int e=1;e<exp_vec[i].length();e++){
						aux_exp = aux_exp + exp_vec[i][e];
					}			
					

					if(exp_vec[i][0]=='-'){


						num1 =  - stof(aux_exp);

						aux_exp = "";

					}else{


						num1 = stof(aux_exp);

						aux_exp = "";

					}

					//calcular num2


					for(int e=1;e<exp_vec[i + 2].length();e++){
						aux_exp = aux_exp + exp_vec[i + 2][e];
					}			

					if(exp_vec[i+2][0]=='-'){


						num2 =  - stof(aux_exp);



						aux_exp = "";

					}else{

						num2 = stof(aux_exp);

						aux_exp = "";

					}


					resultado = num1 * num2;

					if(resultado>=0){
						nuevo_exp_vec.push_back( "+" + to_string(resultado));
					}else{
						nuevo_exp_vec.push_back(to_string(resultado));
					}

					i = i + 2;



				}else{

					nuevo_exp_vec.push_back(exp_vec[i]);					

				}


			}else{

				nuevo_exp_vec.push_back(exp_vec[i]);					

			}

			aux_exp = "";
		}		

	}

	return nuevo_exp_vec;

}




vector<string> resolver_pow(vector<string> exp_vec){

	vector<string> nuevo_exp_vec;

	float resultado = 0;

	string aux_exp = "";
	float num1 = 0;
	float num2 = 0;

	if(hay_pows(exp_vec)){
		for(int i=0;i<exp_vec.size();i++){


			if(exp_vec.size()>i+1){

				if(exp_vec[i + 1][0] == '^'){

					//calcular num1

					for(int e=1;e<exp_vec[i].length();e++){
						aux_exp = aux_exp + exp_vec[i][e];
					}			
					

					if(exp_vec[i][0]=='-'){


						num1 =  - stof(aux_exp);

						aux_exp = "";

					}else{


						num1 = stof(aux_exp);

						aux_exp = "";

					}

					//calcular num2


					for(int e=1;e<exp_vec[i + 2].length();e++){
						aux_exp = aux_exp + exp_vec[i + 2][e];
					}			

					if(exp_vec[i+2][0]=='-'){


						num2 =  - stof(aux_exp);



						aux_exp = "";

					}else{

						num2 = stof(aux_exp);

						aux_exp = "";

					}

					/*
					if(num2 != 0){



					}
					else{
						resultado = 1;
					}

					for(int i=0;i<num2;i++){
						resultado = num1 ^ num2;
					}
					
					*/

					resultado = pow(num1,num2);

					if(resultado>=0){
						nuevo_exp_vec.push_back( "+" + to_string(resultado));
					}else{
						nuevo_exp_vec.push_back(to_string(resultado));
					}

					i = i + 2;



				}else{

					nuevo_exp_vec.push_back(exp_vec[i]);					

				}


			}else{

				nuevo_exp_vec.push_back(exp_vec[i]);					

			}

			aux_exp = "";
		}		

	}

	return nuevo_exp_vec;

}





vector<string> resolver_divisiones(vector<string> exp_vec){

	vector<string> nuevo_exp_vec;

	float resultado = 0;

	string aux_exp = "";
	float num1 = 0;
	float num2 = 0;

	if(hay_divisiones(exp_vec)){
		for(int i=0;i<exp_vec.size();i++){


			if(exp_vec.size()>i+1){

				if(exp_vec[i + 1][0] == '/'){

					//calcular num1

					for(int e=1;e<exp_vec[i].length();e++){
						aux_exp = aux_exp + exp_vec[i][e];
					}			
					

					if(exp_vec[i][0]=='-'){


						num1 =  - stof(aux_exp);

						aux_exp = "";

					}else{


						num1 = stof(aux_exp);

						aux_exp = "";

					}

					//calcular num2


					for(int e=1;e<exp_vec[i + 2].length();e++){
						aux_exp = aux_exp + exp_vec[i + 2][e];
					}			

					if(exp_vec[i+2][0]=='-'){


						num2 =  - stof(aux_exp);



						aux_exp = "";

					}else{

						num2 = stof(aux_exp);

						aux_exp = "";

					}


					resultado = num1 / num2;

					if(resultado>=0){
						nuevo_exp_vec.push_back( "+" + to_string(resultado));
					}else{
						nuevo_exp_vec.push_back(to_string(resultado));
					}

					i = i + 2;



				}else{

					nuevo_exp_vec.push_back(exp_vec[i]);					

				}


			}else{

				nuevo_exp_vec.push_back(exp_vec[i]);					

			}


			aux_exp = "";
		}


		

	}



	return nuevo_exp_vec;

}



vector<string> resolver_mod(vector<string> exp_vec){

	vector<string> nuevo_exp_vec;

	float resultado = 0;

	string aux_exp = "";
	float num1 = 0;
	float num2 = 0;

	if(hay_mods(exp_vec)){
		for(int i=0;i<exp_vec.size();i++){


			if(exp_vec.size()>i+1){

				if(exp_vec[i + 1][0] == '%'){

					//calcular num1

					for(int e=1;e<exp_vec[i].length();e++){
						aux_exp = aux_exp + exp_vec[i][e];
					}			
					

					if(exp_vec[i][0]=='-'){


						num1 =  - stof(aux_exp);

						aux_exp = "";

					}else{


						num1 = stof(aux_exp);

						aux_exp = "";

					}

					//calcular num2


					for(int e=1;e<exp_vec[i + 2].length();e++){
						aux_exp = aux_exp + exp_vec[i + 2][e];
					}			

					if(exp_vec[i+2][0]=='-'){


						num2 =  - stof(aux_exp);



						aux_exp = "";

					}else{

						num2 = stof(aux_exp);

						aux_exp = "";

					}

					int coent = num1 / num2 ;

					resultado = num1-coent*num2;



					if(resultado>=0){
						nuevo_exp_vec.push_back( "+" + to_string(resultado));
					}else{
						nuevo_exp_vec.push_back(to_string(resultado));
					}

					i = i + 2;



				}else{

					nuevo_exp_vec.push_back(exp_vec[i]);					

				}


			}else{

				nuevo_exp_vec.push_back(exp_vec[i]);					

			}


			aux_exp = "";
		}


		

	}



	return nuevo_exp_vec;

}




vector<string> resolver_div(vector<string> exp_vec){

	vector<string> nuevo_exp_vec;

	int resultado = 0;

	string aux_exp = "";
	float num1 = 0;
	float num2 = 0;

	if(hay_divs(exp_vec)){

		for(int i=0;i<exp_vec.size();i++){

			if(exp_vec.size()>i+1){

				if(exp_vec[i + 1][0] == '|'){

					//calcular num1

					for(int e=1;e<exp_vec[i].length();e++){
						aux_exp = aux_exp + exp_vec[i][e];
					}			
					

					if(exp_vec[i][0]=='-'){


						num1 =  - stoi(aux_exp);

						aux_exp = "";

					}else{


						num1 = stoi(aux_exp);

						aux_exp = "";

					}

					//calcular num2


					for(int e=1;e<exp_vec[i + 2].length();e++){
						aux_exp = aux_exp + exp_vec[i + 2][e];
					}			

					if(exp_vec[i+2][0]=='-'){


						num2 =  - stoi(aux_exp);



						aux_exp = "";

					}else{

						
						num2 = stoi(aux_exp);

						aux_exp = "";

					}


					resultado = num1 / num2;

					if(resultado>=0){
						nuevo_exp_vec.push_back( "+" + to_string(resultado));
					}else{
						nuevo_exp_vec.push_back(to_string(resultado));
					}

					i = i + 2;



				}else{

					nuevo_exp_vec.push_back(exp_vec[i]);					

				}


			}else{

				nuevo_exp_vec.push_back(exp_vec[i]);					

			}


			aux_exp = "";
		}


		

	}



	return nuevo_exp_vec;

}



vector<string> resolver_sumas_y_restas(vector<string> exp_vec){

	//hacer sumas y restas

	float resultado = 0;
	string aux_exp;

	vector<string> nuevo_exp_vec;

	for(int i=0;i<exp_vec.size();i++){


		if(exp_vec[i][0]=='-'){
			for(int e=1;e<exp_vec[i].length();e++){
				aux_exp = aux_exp + exp_vec[i][e];
			}			

			resultado = resultado - stof(aux_exp);

			aux_exp = "";

		}else{
			for(int e=1;e<exp_vec[i].length();e++){
				aux_exp = aux_exp + exp_vec[i][e];
			}			

			resultado = resultado + stof(aux_exp);
			aux_exp = "";

		}



	}


	if(resultado>=0){
		nuevo_exp_vec.push_back( "+" + to_string(resultado));
	}else{
		nuevo_exp_vec.push_back(to_string(resultado));
	}


	return nuevo_exp_vec;


}






vector<string> resolver_parentesis(vector<string> exp_vec){

	vector<string> vector_resultado;



	for(int i=0;i<exp_vec.size();i++){

		if(exp_vec[i][0]=='('){

			vector<string> aux_exp;

			int extra_parentesis = 0;


			for(int e=i + 1;e<exp_vec.size();e++){

				if(exp_vec[e][0]=='('){
					extra_parentesis ++;
				}


				if(exp_vec[e][0]==')' and extra_parentesis==0){
					i = e;
					break;
				}else{

					if(exp_vec[e][0]==')'){
						extra_parentesis --;
					}

					aux_exp.push_back(exp_vec[e]);
				}


			}


			while(hay_parentesis(aux_exp)){
				aux_exp = resolver_parentesis(aux_exp);
			}

			
			while(hay_pows(aux_exp)){
				aux_exp = resolver_pow(aux_exp);
			}


			while(hay_divisiones(aux_exp)){
				aux_exp = resolver_divisiones(aux_exp);
			}


			while(hay_productos(aux_exp)){
				aux_exp = resolver_productos(aux_exp);
			}


			while(hay_divs(aux_exp)){
				aux_exp = resolver_div(aux_exp);
			}


			while(hay_mods(aux_exp)){
				aux_exp = resolver_mod(aux_exp);
			}



			aux_exp = resolver_sumas_y_restas(aux_exp);
			


			for(int j=0;j<aux_exp.size();j++){
				vector_resultado.push_back(aux_exp[j]);
			}
			


		}else{

			vector_resultado.push_back(exp_vec[i]);

		}
	}

	



	return vector_resultado;
}


vector<string> resolver_signos(vector<string> exp_vec){

	vector<string> resultado;

	for(int i=0;i<exp_vec.size();i++){
		if(exp_vec[i][0]=='+'){
			
			if(exp_vec[i].length() > 1){
				resultado.push_back(exp_vec[i]);
			}

		}
		else if(exp_vec[i][0]=='-'){

			if(exp_vec[i].length() > 1){
				resultado.push_back(exp_vec[i]);
			}else{


				if(exp_vec.size() > i + 1){

					if(exp_vec[i+1][0] == '+'){
						exp_vec[i+1][0] = '-';
					}
					else if(exp_vec[i+1][0] == '-'){
						exp_vec[i+1][0] = '+';
					}

				}

			}

		}
		else{

			resultado.push_back(exp_vec[i]);
		}

	}


	return resultado;


}














vector<string> resolver(string exp){
	vector<string> exp_vec = separar_por_operacion(exp);


	

	
	while(hay_parentesis(exp_vec)){
		exp_vec = resolver_parentesis(exp_vec);
	}



	while(hay_pows(exp_vec)){
		exp_vec = resolver_pow(exp_vec);
	}


	while(hay_divisiones(exp_vec)){
		exp_vec = resolver_divisiones(exp_vec);
	}


	while(hay_productos(exp_vec)){
		exp_vec = resolver_productos(exp_vec);
	}


	while(hay_divs(exp_vec)){
		exp_vec = resolver_div(exp_vec);
	}


	while(hay_mods(exp_vec)){
		exp_vec = resolver_mod(exp_vec);
	}

	
	//imprimir_elementos(exp_vec);

	exp_vec = resolver_signos(exp_vec);

	//imprimir_elementos(exp_vec);



	exp_vec = resolver_sumas_y_restas(exp_vec);
	


	return exp_vec;

}


int main(int argc, char const *argv[])
{
	cout << resolver(argv[1])[0] << endl;
	return 0;
}
