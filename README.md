# Assento de Ocupação Inteligente

O assento de ocupação inteligente é um sensor para ser acoplado à uma cadeira que detecta a presença de pessoas sentadas à cadeira e emite um pacote na rede local quando o usuário se levanta para avisar sua ausência do local de trabalho. Esse sensor funciona em conjunto com uma aplicação que roda como um servidor na estação de trabalho de um usuário e, ao detectar o aviso de que seu usuário se levantou da cadeira, após 3 segundos a tela da estação é bloqueada para que o usuário, quando volte, tenha que colocar sua senha para desbloqueio.

O objetivo é servir como uma medida de segurança para que os usuários não se preocupem em lembrar de bloquear a tela dos dispositivos quando se levantam. O dispositivo faz o sensoriamento da presença diretamente e não é dependente de outros dispositivos secundários que podem virar outro motivo para preocupação do usuário (ter um cartão RFID precisa que o usuário se preocupe em manter o cartão consigo, o celular pode ser deixado na mesa e não é uma medida de presença, etc...).

## Funcionalidades

Esse projeto terá: 

* Versão do servidor para Linux e Windows
* Identificação de cada cadeira
* Uso do servidor para configuração do acesso à rede do sensor
* Autenticação na comunicação

## Conteúdos do repositório e ferramentas de acesso

* `diagram/`: Todos os esquemáticos envolvendo o circuito. Programas utilizados serão o KiCAD e o LTSpice.
* `server/`: Código da aplicação do servidor
* `controller/`: Código do controlador