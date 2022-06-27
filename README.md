# projeto_Qt

Projeto para Avaliação da disciplina Técnicas de Programação_EE_2022.1

Esse aplicativo pode ser usado para pesquisa, controle, cadastro, exclusão, atualização e geração de um arquivo .csv de funcionários e clientes de um estabelecimento comercial.

Há uma tela inicial de login onde pode ser cadastrado em um banco de dados pessoas com autorização de acesso, obtendo assim um controle maior sobre esses dados.

Uma segunda janela é aberta após a autenticação onde, estão presentes duas abas (tabWidget). Uma representa uma base de dados dos funcionários e a outra representa uma base de dados dos clientes. Foi utilizado o SQL Lite Studio para gerar o banco de dados.

Em cada aba existem 3 botões, um para gerar o cadastro, outro para excluir um cadastro e um terceiro para gerar o arquivo .csv. Em Filtro Colunas, é possível realizar uma pesquisa filtrando por cada campo presente na tabela apresentada. Pode ser digitado o que se deseja pesquisar no campo: Digite algo para pesquisar. Ambas as tabelas, Funcionários e Clientes, possuem essas funcionalidades.

Na aba Funcionários, logo abaixo da tabela onde consta o registro dos mesmos, pode ser visualizado os valores: Total dos Salários, Maior Salário e a quantidade de registros encontrados. O Total dos Salários mostra a soma de todos os salários presentes na tabela. Se for efetudo um filtro, esse valor irá atualizar para a nova pesquisa. Já o Maior Salário, irá mostrar o valor do maior salário dos itens que constam na tabela. Esse valor também é atualizado de acordo com a pesquisa. O próximo valor mostrado é Registros encontrados. Nele será visualizado o total de registros da pesquisa. Também é atualizado conforme aumenta ou diminui o número de itens na tabela.

Na aba Clientes, há logo abaixo da tabela o Registros encontrados. Ele tem a mesma funcionalidade descrita na aba Funcionários.
