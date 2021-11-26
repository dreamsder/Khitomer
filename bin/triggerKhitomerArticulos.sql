delimiter |

DROP TRIGGER if exists ins_suma_stock_faltante_Articulos;

 CREATE TRIGGER ins_suma_stock_faltante_Articulos AFTER UPDATE ON Articulos
    FOR EACH ROW BEGIN
   delete from FaltaStock;
   
   
   insert into FaltaStock (cantidadArticulosSinStock,codigoArticulo)
  
SELECT 

  case when AR.cantidadMinimaStock<= (SELECT
  sum(case when TDOC.afectaStock=1 then DOCL.cantidad else (DOCL.cantidad*-1) end)

from

   Documentos DOC

   join DocumentosLineas DOCL on DOCL.codigoDocumento=DOC.codigoDocumento  

  and DOC.codigoTipoDocumento=DOCL.codigoTipoDocumento

  join TipoDocumento TDOC on TDOC.codigoTipoDocumento=DOC.codigoTipoDocumento

  where TDOC.afectaStock!=0 and DOC.codigoEstadoDocumento in ('E','G','P') and DOCL.codigoArticulo=AR.codigoArticulo

  and DOC.fechaHoraGuardadoDocumentoSQL>= (SELECT DOCS.fechaHoraGuardadoDocumentoSQL FROM Documentos DOCS

  where DOCS.codigoTipoDocumento=8

  and DOCS.codigoEstadoDocumento in ('E','G')

  order by DOCS.codigoDocumento desc limit 1))
  then 0 else 1 end,
  AR.codigoArticulo

  from Articulos AR
  group by AR.codigoArticulo;

 
  END
 |
delimiter ;
