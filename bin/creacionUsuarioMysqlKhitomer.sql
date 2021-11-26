GRANT ALL ON *.* TO khitomer@'%' IDENTIFIED BY 'khitomer' ;
SET PASSWORD FOR khitomer@'%'=OLD_PASSWORD('khitomer');

GRANT ALL ON *.* TO khitomer@'localhost' IDENTIFIED BY 'khitomer' ;
SET PASSWORD FOR khitomer@'localhost'=OLD_PASSWORD('khitomer');

