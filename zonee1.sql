--------------------------------------------------------
--  Fichier créé - mercredi-juin-17-2020   
--------------------------------------------------------
--------------------------------------------------------
--  DDL for Table ZONE
--------------------------------------------------------

  CREATE TABLE "SYSTEM"."ZONE" 
   (	"ID_ZONE" NUMBER, 
	"DIMENSION" NUMBER, 
	"ETAT" VARCHAR2(20 BYTE), 
	"DESCRIPTION" VARCHAR2(20 BYTE)
   ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
REM INSERTING into SYSTEM.ZONE
SET DEFINE OFF;
Insert into SYSTEM.ZONE (ID_ZONE,DIMENSION,ETAT,DESCRIPTION) values ('5','10','traitee','stillnotready');
Insert into SYSTEM.ZONE (ID_ZONE,DIMENSION,ETAT,DESCRIPTION) values ('7','10','traitee','ready');
Insert into SYSTEM.ZONE (ID_ZONE,DIMENSION,ETAT,DESCRIPTION) values ('6','15','traitee','stillnotready');
Insert into SYSTEM.ZONE (ID_ZONE,DIMENSION,ETAT,DESCRIPTION) values ('9','18','traitee','stillnotready');
Insert into SYSTEM.ZONE (ID_ZONE,DIMENSION,ETAT,DESCRIPTION) values ('1','6','fffff','fffff');
Insert into SYSTEM.ZONE (ID_ZONE,DIMENSION,ETAT,DESCRIPTION) values ('2','10','ggrr','grg');
Insert into SYSTEM.ZONE (ID_ZONE,DIMENSION,ETAT,DESCRIPTION) values ('3','2','traitee','ready');
Insert into SYSTEM.ZONE (ID_ZONE,DIMENSION,ETAT,DESCRIPTION) values ('15','50','sassa','asasa');
Insert into SYSTEM.ZONE (ID_ZONE,DIMENSION,ETAT,DESCRIPTION) values ('4','3','traitee','hiuhii');
--------------------------------------------------------
--  DDL for Index ZONE_PK
--------------------------------------------------------

  CREATE UNIQUE INDEX "SYSTEM"."ZONE_PK" ON "SYSTEM"."ZONE" ("ID_ZONE") 
  PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM" ;
--------------------------------------------------------
--  DDL for Trigger ZONE_TRG
--------------------------------------------------------

  CREATE OR REPLACE TRIGGER "SYSTEM"."ZONE_TRG" 
BEFORE INSERT ON ZONE 
FOR EACH ROW 
BEGIN
  <<COLUMN_SEQUENCES>>
  BEGIN
    IF INSERTING AND :NEW.ID_ZONE IS NULL THEN
      SELECT ZONE_SEQ4.NEXTVAL INTO :NEW.ID_ZONE FROM SYS.DUAL;
    END IF;
  END COLUMN_SEQUENCES;
END;
/
ALTER TRIGGER "SYSTEM"."ZONE_TRG" ENABLE;
--------------------------------------------------------
--  Constraints for Table ZONE
--------------------------------------------------------

  ALTER TABLE "SYSTEM"."ZONE" ADD CONSTRAINT "ZONE_PK" PRIMARY KEY ("ID_ZONE")
  USING INDEX PCTFREE 10 INITRANS 2 MAXTRANS 255 COMPUTE STATISTICS 
  STORAGE(INITIAL 65536 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
  PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT FLASH_CACHE DEFAULT CELL_FLASH_CACHE DEFAULT)
  TABLESPACE "SYSTEM"  ENABLE;
  ALTER TABLE "SYSTEM"."ZONE" MODIFY ("ID_ZONE" NOT NULL ENABLE);
