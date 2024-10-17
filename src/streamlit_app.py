import streamlit as st
import os
import subprocess

# Titre de l'application
st.title('Exécution de code C++ avec Streamlit')

# Lecture du fichier main.cpp
cpp_file_path = 'main.cpp'
if os.path.exists(cpp_file_path):
    st.subheader('Contenu du fichier main.cpp')
    with open(cpp_file_path, 'r') as file:
        cpp_code = file.read()
    st.code(cpp_code, language='cpp')

    # Bouton pour compiler et exécuter le code
    if st.button('Compiler et exécuter le code'):
        # Compilation du fichier main.cpp
        compile_command = f'g++ {cpp_file_path} -o output'
        compile_process = subprocess.run(compile_command, shell=True, capture_output=True, text=True)
        
        if compile_process.returncode != 0:
            st.error('Erreur lors de la compilation')
            st.text(compile_process.stderr)
        else:
            st.success('Compilation réussie!')
            # Exécution du fichier compilé
            execute_command = './output'
            execute_process = subprocess.run(execute_command, shell=True, capture_output=True, text=True)
            
            if execute_process.returncode != 0:
                st.error('Erreur lors de l\'exécution')
                st.text(execute_process.stderr)
            else:
                st.subheader('Résultat de l\'exécution:')
                st.text(execute_process.stdout)
else:
    st.error(f"Le fichier {cpp_file_path} n'existe pas dans le répertoire courant.")
