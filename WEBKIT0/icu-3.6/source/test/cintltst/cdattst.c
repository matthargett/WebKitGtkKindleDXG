/********************************************************************
 * COPYRIGHT: 
 * Copyright (c) 1997-2006, International Business Machines Corporation and
 * others. All Rights Reserved.
 ********************************************************************/
/********************************************************************************
*
* File CDATTST.C
*
* Modification History:
*        Name                     Description            
*     Madhu Katragadda               Creation
*********************************************************************************
*/

/* C API TEST FOR DATE FORMAT */

#include "unicode/utypes.h"

#if !UCONFIG_NO_FORMATTING

#include "unicode/uloc.h"
#include "unicode/udat.h"
#include "unicode/ucal.h"
#include "unicode/unum.h"
#include "unicode/ustring.h"
#include "cintltst.h"
#include "cdattst.h"
#include "cformtst.h"
#include "cmemory.h"

#include <math.h>

static void TestExtremeDates(void);
static void TestAllLocales(void);

#define LEN(a) (sizeof(a)/sizeof(a[0]))

void addDateForTest(TestNode** root);

#define TESTCASE(x) addTest(root, &x, "tsformat/cdattst/" #x)

void addDateForTest(TestNode** root)
{
    TESTCASE(TestDateFormat);
    TESTCASE(TestSymbols);
    TESTCASE(TestDateFormatCalendar);
    TESTCASE(TestExtremeDates);
    TESTCASE(TestAllLocales);
}
/* Testing the DateFormat API */
static void TestDateFormat()
{
    UDateFormat *def, *fr, *it, *de, *def1, *fr_pat;
    UDateFormat *any;
    UDateFormat *copy;
    UErrorCode status = U_ZERO_ERROR;
    UChar* result = NULL;
    const UCalendar *cal;
    const UNumberFormat *numformat1, *numformat2;
    UChar temp[30];
    int32_t numlocales;
    UDate d1;
    int i;
    int32_t resultlength;
    int32_t resultlengthneeded;
    int32_t parsepos;
    UDate d = 837039928046.0;
    double num = -10456.37;
    /*const char* str="yyyy.MM.dd G 'at' hh:mm:ss z";
    const char t[]="2/3/76 2:50 AM";*/
    /*Testing udat_open() to open a dateformat */

    ctest_setTimeZone(NULL, &status);

    log_verbose("\nTesting udat_open() with various parameters\n");
    fr = udat_open(UDAT_FULL, UDAT_DEFAULT, "fr_FR", NULL,0, NULL, 0,&status);
    if(U_FAILURE(status))
    {
        log_err("FAIL: error in creating the dateformat using full time style with french locale\n %s\n", 
            myErrorName(status) );
        return;
    }
    /* this is supposed to open default date format, but later on it treats it like it is "en_US" 
       - very bad if you try to run the tests on machine where default locale is NOT "en_US" */
    /* def = udat_open(UDAT_SHORT, UDAT_SHORT, NULL, NULL, 0, &status); */
    def = udat_open(UDAT_SHORT, UDAT_SHORT, "en_US", NULL, 0,NULL, 0, &status);
    if(U_FAILURE(status))
    {
        log_err("FAIL: error in creating the dateformat using short date and time style\n %s\n", 
            myErrorName(status) );
        return;
    }
    it = udat_open(UDAT_DEFAULT, UDAT_MEDIUM, "it_IT", NULL, 0, NULL, 0,&status);
    if(U_FAILURE(status))
    {
        log_err("FAIL: error in creating the dateformat using medium date style with italian locale\n %s\n", 
            myErrorName(status) );
        return;
    }
    de = udat_open(UDAT_LONG, UDAT_LONG, "de_DE", NULL, 0, NULL, 0,&status);
    if(U_FAILURE(status))
    {
        log_err("FAIL: error in creating the dateformat using long time and date styles with german locale\n %s\n",
            myErrorName(status));
        return;
    }
    /*creating a default dateformat */
    def1 = udat_open(UDAT_SHORT, UDAT_SHORT, NULL, NULL, 0,NULL, 0, &status);
    if(U_FAILURE(status))
    {
        log_err("FAIL: error in creating the dateformat using short date and time style\n %s\n", 
            myErrorName(status) );
        return;
    }


    /*Testing udat_getAvailable() and udat_countAvailable()*/ 
    log_verbose("\nTesting getAvailableLocales and countAvailable()\n");
    numlocales=udat_countAvailable();
    /* use something sensible w/o hardcoding the count */
    if(numlocales < 0)
        log_data_err("FAIL: error in countAvailable\n");
    log_verbose("The number of locales for which date/time formatting patterns are available is %d\n", numlocales);
    
    for(i=0;i<numlocales;i++) {
      UErrorCode subStatus = U_ZERO_ERROR;
      log_verbose("Testing open of %s\n", udat_getAvailable(i));
      any = udat_open(UDAT_SHORT, UDAT_SHORT, udat_getAvailable(i), NULL ,0, NULL, 0, &subStatus);
      if(U_FAILURE(subStatus)) {
        log_data_err("FAIL: date format %s (getAvailable(%d)) is not instantiable: %s\n", udat_getAvailable(i), i, u_errorName(subStatus));
      }
      udat_close(any);
    }

    /*Testing udat_clone()*/
    log_verbose("\nTesting the udat_clone() function of date format\n");
    copy=udat_clone(def, &status);
    if(U_FAILURE(status)){
        log_err("Error in creating the clone using udat_clone: %s\n", myErrorName(status) );
    }
    /*if(def != copy)
        log_err("Error in udat_clone");*/ /*how should i check for equality???? */
    
    /*Testing udat_format()*/
    log_verbose("\nTesting the udat_format() function of date format\n");
    u_uastrcpy(temp, "7/10/96 4:05 PM");
    /*format using def */
    resultlength=0;
    resultlengthneeded=udat_format(def, d, NULL, resultlength, NULL, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR)
    {
        status=U_ZERO_ERROR;
        resultlength=resultlengthneeded+1;
        if(result != NULL) {
            free(result);
            result = NULL;
        }
        result=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_format(def, d, result, resultlength, NULL, &status);
    }
    if(U_FAILURE(status) || !result)
    {
        log_err("FAIL: Error in formatting using udat_format(.....) %s\n", myErrorName(status) );
        return;
    }
    else
        log_verbose("PASS: formatting successful\n");
    if(u_strcmp(result, temp)==0)
        log_verbose("PASS: Date Format for US locale successful uisng udat_format()\n");
    else
        log_err("FAIL: Date Format for US locale failed using udat_format()\n");
    /*format using fr */
    
    u_unescape("10 juil. 96 16 h 05 HAP (\\u00c9UA)", temp, 30);
    if(result != NULL) {
        free(result);
        result = NULL;
    }
    result=myDateFormat(fr, d);
    if(u_strcmp(result, temp)==0)
        log_verbose("PASS: Date Format for french locale successful using udat_format()\n");
    else
        log_data_err("FAIL: Date Format for french locale failed using udat_format(). Expected:\n");
    /*format using it */
    u_uastrcpy(temp, "10/lug/96 16:05:28");
    
    if(u_strcmp(myDateFormat(it,d), temp)==0)
        log_verbose("PASS: Date Format for italian locale successful uisng udat_format()\n");
    else
        log_data_err("FAIL: Date Format for italian locale failed using udat_format()\n");

    
    /*Testing parsing using udat_parse()*/
    log_verbose("\nTesting parsing using udat_parse()\n");
    u_uastrcpy(temp,"2/3/76 2:50 AM");
    parsepos=0;
    status=U_ZERO_ERROR;
    
    d1=udat_parse(def, temp, u_strlen(temp), &parsepos, &status);
    if(U_FAILURE(status))
    {
        log_err("FAIL: Error in parsing using udat_parse(.....) %s\n", myErrorName(status) );
    }
    else
        log_verbose("PASS: parsing succesful\n");
    /*format it back and check for equality */
    
    
    if(u_strcmp(myDateFormat(def, d1),temp)!=0)
        log_err("FAIL: error in parsing\n");

    /*Testing parsing using udat_parse()*/
    log_verbose("\nTesting parsing using udat_parse()\n");
    u_uastrcpy(temp,"2/Don't parse this part");
    status=U_ZERO_ERROR;
    
    d1=udat_parse(def, temp, u_strlen(temp), NULL, &status);
    if(status != U_PARSE_ERROR)
    {
        log_err("FAIL: udat_parse(\"bad string\") passed when it should have failed\n");
    }
    else
        log_verbose("PASS: parsing succesful\n");
        
        
    
    /*Testing udat_openPattern()  */
    status=U_ZERO_ERROR;
    log_verbose("\nTesting the udat_openPattern with a specified pattern\n");
    /*for french locale */
    fr_pat=udat_open(UDAT_IGNORE, UDAT_IGNORE,"fr_FR",NULL,0,temp, u_strlen(temp), &status);
    if(U_FAILURE(status))
    {
        log_err("FAIL: Error in creating a date format using udat_openPattern \n %s\n", 
            myErrorName(status) );
    }
    else
        log_verbose("PASS: creating dateformat using udat_openPattern() succesful\n");

    
        /*Testing applyPattern and toPattern */
    log_verbose("\nTesting applyPattern and toPattern()\n");
    udat_applyPattern(def1, FALSE, temp, u_strlen(temp));
    log_verbose("Extracting the pattern\n");

    resultlength=0;
    resultlengthneeded=udat_toPattern(def1, FALSE, NULL, resultlength, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR)
    {
        status=U_ZERO_ERROR;
        resultlength=resultlengthneeded + 1;
        result=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_toPattern(def1, FALSE, result, resultlength, &status);
    }
    if(U_FAILURE(status))
    {
        log_err("FAIL: error in extracting the pattern from UNumberFormat\n %s\n", 
            myErrorName(status) );
    }
    if(u_strcmp(result, temp)!=0)
        log_err("FAIL: Error in extracting the pattern\n");
    else
        log_verbose("PASS: applyPattern and toPattern work fine\n");
    
    if(result != NULL) {
        free(result);    
        result = NULL;
    }
    
    
    /*Testing getter and setter functions*/
    /*isLenient and setLenient()*/
    log_verbose("\nTesting the isLenient and setLenient properties\n");
    udat_setLenient(fr, udat_isLenient(it));
    if(udat_isLenient(fr) != udat_isLenient(it)) 
        log_err("ERROR: setLenient() failed\n");
    else
        log_verbose("PASS: setLenient() successful\n");


    /*Test get2DigitYearStart set2DigitYearStart */
    log_verbose("\nTesting the get and set 2DigitYearStart properties\n");
    d1= udat_get2DigitYearStart(fr_pat,&status);
    if(U_FAILURE(status)) {
            log_err("ERROR: udat_get2DigitYearStart failed %s\n", myErrorName(status) );
    }
    status = U_ZERO_ERROR;
    udat_set2DigitYearStart(def1 ,d1, &status);
    if(U_FAILURE(status)) {
        log_err("ERROR: udat_set2DigitYearStart failed %s\n", myErrorName(status) );
    }
    if(udat_get2DigitYearStart(fr_pat, &status) != udat_get2DigitYearStart(def1, &status))
        log_err("FAIL: error in set2DigitYearStart\n");
    else
        log_verbose("PASS: set2DigitYearStart successful\n");
    /*try setting it to another value */
    udat_set2DigitYearStart(de, 2000.0, &status);
    if(U_FAILURE(status)){
        log_verbose("ERROR: udat_set2DigitYearStart failed %s\n", myErrorName(status) );
    }
    if(udat_get2DigitYearStart(de, &status) != 2000)
        log_err("FAIL: error in set2DigitYearStart\n");
    else
        log_verbose("PASS: set2DigitYearStart successful\n");

    

    /*Test getNumberFormat() and setNumberFormat() */
    log_verbose("\nTesting the get and set NumberFormat properties of date format\n");
    numformat1=udat_getNumberFormat(fr_pat);
    udat_setNumberFormat(def1, numformat1);
    numformat2=udat_getNumberFormat(def1);
    if(u_strcmp(myNumformat(numformat1, num), myNumformat(numformat2, num)) !=0)
        log_err("FAIL: error in setNumberFormat or getNumberFormat()\n");
    else
        log_verbose("PASS:setNumberFormat and getNumberFormat succesful\n");

    /*try setting the number format to another format */
    numformat1=udat_getNumberFormat(def);
    udat_setNumberFormat(def1, numformat1);
    numformat2=udat_getNumberFormat(def1);
    if(u_strcmp(myNumformat(numformat1, num), myNumformat(numformat2, num)) !=0)
        log_err("FAIL: error in setNumberFormat or getNumberFormat()\n");
    else
        log_verbose("PASS: setNumberFormat and getNumberFormat succesful\n");



    /*Test getCalendar and setCalendar*/
    log_verbose("\nTesting the udat_getCalendar() and udat_setCalendar() properties\n");
    cal=udat_getCalendar(fr_pat);
    
    
    udat_setCalendar(def1, cal);
    if(!ucal_equivalentTo(udat_getCalendar(fr_pat), udat_getCalendar(def1)))
        log_err("FAIL: Error in setting and getting the calendar\n");
    else
        log_verbose("PASS: getting and setting calendar successful\n");
        
    if(result!=NULL) {
        free(result);
    }
    
    /*Closing the UDateForamt */
    udat_close(def);
    udat_close(fr);
    udat_close(it);
    udat_close(de);
    udat_close(def1);
    udat_close(fr_pat);
    udat_close(copy);
    
    ctest_resetTimeZone();
}

/*Testing udat_getSymbols() and udat_setSymbols() and udat_countSymbols()*/
static void TestSymbols()
{
    UDateFormat *def, *fr;
    UErrorCode status = U_ZERO_ERROR;
    UChar *value=NULL; 
    UChar *result = NULL;
    int32_t resultlength;
    int32_t resultlengthout;
    UChar *pattern;
        

    /*creating a dateformat with french locale */
    log_verbose("\ncreating a date format with french locale\n");
    fr = udat_open(UDAT_FULL, UDAT_DEFAULT, "fr_FR", NULL, 0, NULL, 0, &status);
    if(U_FAILURE(status))
    {
        log_err("error in creating the dateformat using full time style with french locale\n %s\n", 
            myErrorName(status) );
        return;
    }
    /*creating a default dateformat */
    log_verbose("\ncreating a date format with default locale\n");
    /* this is supposed to open default date format, but later on it treats it like it is "en_US" 
       - very bad if you try to run the tests on machine where default locale is NOT "en_US" */
    /* def = udat_open(UDAT_DEFAULT,UDAT_DEFAULT ,NULL, NULL, 0, &status); */
    def = udat_open(UDAT_DEFAULT,UDAT_DEFAULT ,"en_US", NULL, 0, NULL, 0, &status);
    if(U_FAILURE(status))
    {
        log_err("error in creating the dateformat using short date and time style\n %s\n", 
            myErrorName(status) );
        return;
    }
    
    
    /*Testing countSymbols, getSymbols and setSymbols*/
    log_verbose("\nTesting countSymbols\n");
    /*since the month names has the last string empty and week names are 1 based 1.e first string in the weeknames array is empty */
    if(udat_countSymbols(def, UDAT_ERAS)!=2 || udat_countSymbols(def, UDAT_MONTHS)!=12 || 
        udat_countSymbols(def, UDAT_SHORT_MONTHS)!=12 || udat_countSymbols(def, UDAT_WEEKDAYS)!=8 ||
        udat_countSymbols(def, UDAT_SHORT_WEEKDAYS)!=8 || udat_countSymbols(def, UDAT_AM_PMS)!=2 ||
        udat_countSymbols(def, UDAT_QUARTERS) != 4 || udat_countSymbols(def, UDAT_SHORT_QUARTERS) != 4 ||
        udat_countSymbols(def, UDAT_LOCALIZED_CHARS)!=1)
    {
        log_err("FAIL: error in udat_countSymbols\n");
    }
    else
        log_verbose("PASS: udat_countSymbols() successful\n");

    /*testing getSymbols*/
    log_verbose("\nTesting getSymbols\n");
    pattern=(UChar*)malloc(sizeof(UChar) * 10);
    u_uastrcpy(pattern, "jeudi");
    resultlength=0;
    resultlengthout=udat_getSymbols(fr, UDAT_WEEKDAYS, 5 , NULL, resultlength, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR)
    {
        status=U_ZERO_ERROR;
        resultlength=resultlengthout+1;
        if(result != NULL) {
            free(result);
            result = NULL;
        }
        result=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_getSymbols(fr, UDAT_WEEKDAYS, 5, result, resultlength, &status);
        
    }
    if(U_FAILURE(status))
    {
        log_err("FAIL: Error in udat_getSymbols().... %s\n", myErrorName(status) );
    }
    else
        log_verbose("PASS: getSymbols succesful\n");

    if(u_strcmp(result, pattern)==0)
        log_verbose("PASS: getSymbols retrieved the right value\n");
    else
        log_data_err("FAIL: getSymbols retrieved the wrong value\n");

    /*run series of tests to test getsymbols regressively*/
    log_verbose("\nTesting getSymbols() regressively\n");
    VerifygetSymbols(fr, UDAT_WEEKDAYS, 1, "dimanche");
    VerifygetSymbols(def, UDAT_WEEKDAYS, 1, "Sunday");
    VerifygetSymbols(fr, UDAT_SHORT_WEEKDAYS, 7, "sam.");
    VerifygetSymbols(def, UDAT_SHORT_WEEKDAYS, 7, "Sat");
    VerifygetSymbols(def, UDAT_MONTHS, 11, "December");
    VerifygetSymbols(def, UDAT_MONTHS, 0, "January");
    VerifygetSymbols(fr, UDAT_ERAS, 0, "av. J.-C.");
    VerifygetSymbols(def, UDAT_AM_PMS, 0, "AM");
    VerifygetSymbols(def, UDAT_AM_PMS, 1, "PM");
    VerifygetSymbols(fr, UDAT_SHORT_MONTHS, 0, "janv.");
    VerifygetSymbols(def, UDAT_SHORT_MONTHS, 11, "Dec");
    VerifygetSymbols(fr, UDAT_QUARTERS, 0, "1er trimestre");
    VerifygetSymbols(def, UDAT_QUARTERS, 3, "4th quarter");
    VerifygetSymbols(fr, UDAT_SHORT_QUARTERS, 1, "T2");
    VerifygetSymbols(def, UDAT_SHORT_QUARTERS, 2, "Q3");
    VerifygetSymbols(def,UDAT_LOCALIZED_CHARS, 0, "GyMdkHmsSEDFwWahKzYeugAZvcL");


    if(result != NULL) {
        free(result);
        result = NULL;
    }
free(pattern);    
    
    log_verbose("\nTesting setSymbols\n");
    /*applying the pattern so that setSymbolss works */
    resultlength=0;
    resultlengthout=udat_toPattern(fr, FALSE, NULL, resultlength, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR)
    {
        status=U_ZERO_ERROR;
        resultlength=resultlengthout + 1;
        pattern=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_toPattern(fr, FALSE, pattern, resultlength, &status);
    }
    if(U_FAILURE(status))
    {
        log_err("FAIL: error in extracting the pattern from UNumberFormat\n %s\n", 
            myErrorName(status) );
    }
    
    udat_applyPattern(def, FALSE, pattern, u_strlen(pattern));
    resultlength=0;
    resultlengthout=udat_toPattern(def, FALSE, NULL, resultlength,&status);
    if(status==U_BUFFER_OVERFLOW_ERROR)
    {
        status=U_ZERO_ERROR;
        resultlength=resultlengthout + 1;
        if(result != NULL) {
            free(result);
            result = NULL;
        }
        result=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_toPattern(fr, FALSE,result, resultlength, &status);
    }
    if(U_FAILURE(status))
    {
        log_err("FAIL: error in extracting the pattern from UNumberFormat\n %s\n", 
            myErrorName(status) );
    }
    if(u_strcmp(result, pattern)==0)
        log_verbose("Pattern applied properly\n");
    else
        log_err("pattern could not be applied properly\n");

free(pattern);
    /*testing set symbols */
    resultlength=0;
    resultlengthout=udat_getSymbols(fr, UDAT_MONTHS, 11 , NULL, resultlength, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR){
        status=U_ZERO_ERROR;
        resultlength=resultlengthout+1;
        if(result != NULL) {
            free(result);
            result = NULL;
        }
        result=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_getSymbols(fr, UDAT_MONTHS, 11, result, resultlength, &status);
        
    }
    if(U_FAILURE(status))
        log_err("FAIL: error in getSymbols() %s\n", myErrorName(status) );
    resultlength=resultlengthout+1;
    
    udat_setSymbols(def, UDAT_MONTHS, 11, result, resultlength, &status);
    if(U_FAILURE(status))
        {
            log_err("FAIL: Error in udat_setSymbols() : %s\n", myErrorName(status) );
        }
    else
        log_verbose("PASS: SetSymbols successful\n");
    
    resultlength=0;
    resultlengthout=udat_getSymbols(def, UDAT_MONTHS, 11, NULL, resultlength, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR){
        status=U_ZERO_ERROR;
        resultlength=resultlengthout+1;
        value=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_getSymbols(def, UDAT_MONTHS, 11, value, resultlength, &status);
    }
    if(U_FAILURE(status))
        log_err("FAIL: error in retrieving the value using getSymbols i.e roundtrip\n");
    
    if(u_strcmp(result, value)!=0)
        log_data_err("FAIL: Error in settting and getting symbols\n");
    else
        log_verbose("PASS: setSymbols successful\n");
    
    
    /*run series of tests to test setSymbols regressively*/
    log_verbose("\nTesting setSymbols regressively\n");
    VerifysetSymbols(def, UDAT_ERAS, 0, "BeforeChrist");
    VerifysetSymbols(def, UDAT_ERA_NAMES, 1, "AnnoDomini");
    VerifysetSymbols(def, UDAT_WEEKDAYS, 1, "Sundayweek");
    VerifysetSymbols(def, UDAT_SHORT_WEEKDAYS, 7, "Satweek");
    VerifysetSymbols(def, UDAT_NARROW_WEEKDAYS, 4, "M");
    VerifysetSymbols(def, UDAT_STANDALONE_WEEKDAYS, 1, "Sonntagweek");
    VerifysetSymbols(def, UDAT_STANDALONE_SHORT_WEEKDAYS, 7, "Sams");
    VerifysetSymbols(def, UDAT_STANDALONE_NARROW_WEEKDAYS, 4, "V");
    VerifysetSymbols(fr, UDAT_MONTHS, 11, "december");
    VerifysetSymbols(fr, UDAT_SHORT_MONTHS, 0, "Jan");
    VerifysetSymbols(fr, UDAT_NARROW_MONTHS, 1, "R");
    VerifysetSymbols(fr, UDAT_STANDALONE_MONTHS, 11, "dezember");
    VerifysetSymbols(fr, UDAT_STANDALONE_SHORT_MONTHS, 7, "Aug");
    VerifysetSymbols(fr, UDAT_STANDALONE_NARROW_MONTHS, 2, "M");
    VerifysetSymbols(fr, UDAT_QUARTERS, 0, "1. Quart");
    VerifysetSymbols(fr, UDAT_SHORT_QUARTERS, 1, "QQ2");
    VerifysetSymbols(fr, UDAT_STANDALONE_QUARTERS, 2, "3rd Quar.");
    VerifysetSymbols(fr, UDAT_STANDALONE_SHORT_QUARTERS, 3, "4QQ");

    
    /*run series of tests to test get and setSymbols regressively*/
    log_verbose("\nTesting get and set symbols regressively\n");
    VerifygetsetSymbols(fr, def, UDAT_WEEKDAYS, 1);
    VerifygetsetSymbols(fr, def, UDAT_WEEKDAYS, 7);
    VerifygetsetSymbols(fr, def, UDAT_SHORT_WEEKDAYS, 1);
    VerifygetsetSymbols(fr, def, UDAT_SHORT_WEEKDAYS, 7);
    VerifygetsetSymbols(fr, def, UDAT_MONTHS, 0);
    VerifygetsetSymbols(fr, def, UDAT_SHORT_MONTHS, 0);
    VerifygetsetSymbols(fr, def, UDAT_ERAS,1);
    VerifygetsetSymbols(fr, def, UDAT_LOCALIZED_CHARS, 0);
    VerifygetsetSymbols(fr, def, UDAT_AM_PMS, 1);


    /*closing*/
    
    udat_close(fr);
    udat_close(def);
    if(result != NULL) {
        free(result);
        result = NULL;
    }
    free(value);
    
}

/**
 * Test DateFormat(Calendar) API
 */
static void TestDateFormatCalendar() {
    UDateFormat *date=0, *time=0, *full=0;
    UCalendar *cal=0;
    UChar buf[256];
    char cbuf[256];
    int32_t pos;
    UDate when;
    UErrorCode ec = U_ZERO_ERROR;

    ctest_setTimeZone(NULL, &ec);

    /* Create a formatter for date fields. */
    date = udat_open(UDAT_NONE, UDAT_SHORT, "en_US", NULL, 0, NULL, 0, &ec);
    if (U_FAILURE(ec)) {
        log_err("FAIL: udat_open(NONE, SHORT, en_US) failed with %s\n", 
                u_errorName(ec));
        goto FAIL;
    }

    /* Create a formatter for time fields. */
    time = udat_open(UDAT_SHORT, UDAT_NONE, "en_US", NULL, 0, NULL, 0, &ec);
    if (U_FAILURE(ec)) {
        log_err("FAIL: udat_open(SHORT, NONE, en_US) failed with %s\n", 
                u_errorName(ec));
        goto FAIL;
    }

    /* Create a full format for output */
    full = udat_open(UDAT_FULL, UDAT_FULL, "en_US", NULL, 0, NULL, 0, &ec);
    if (U_FAILURE(ec)) {
        log_err("FAIL: udat_open(FULL, FULL, en_US) failed with %s\n", 
                u_errorName(ec));
        goto FAIL;
    }

    /* Create a calendar */
    cal = ucal_open(NULL, 0, "en_US", UCAL_GREGORIAN, &ec);
    if (U_FAILURE(ec)) {
        log_err("FAIL: ucal_open(en_US) failed with %s\n", 
                u_errorName(ec));
        goto FAIL;
    }

    /* Parse the date */
    ucal_clear(cal);
    u_uastrcpy(buf, "4/5/2001");
    pos = 0;
    udat_parseCalendar(date, cal, buf, -1, &pos, &ec);
    if (U_FAILURE(ec)) {
        log_err("FAIL: udat_parseCalendar(4/5/2001) failed at %d with %s\n",
                pos, u_errorName(ec));
        goto FAIL;
    }

    /* Parse the time */
    u_uastrcpy(buf, "5:45 PM");
    pos = 0;
    udat_parseCalendar(time, cal, buf, -1, &pos, &ec);
    if (U_FAILURE(ec)) {
        log_err("FAIL: udat_parseCalendar(17:45) failed at %d with %s\n",
                pos, u_errorName(ec));
        goto FAIL;
    }
    
    /* Check result */
    when = ucal_getMillis(cal, &ec);
    if (U_FAILURE(ec)) {
        log_err("FAIL: ucal_getMillis() failed with %s\n", u_errorName(ec));
        goto FAIL;
    }
    udat_format(full, when, buf, sizeof(buf), NULL, &ec);
    if (U_FAILURE(ec)) {
        log_err("FAIL: udat_format() failed with %s\n", u_errorName(ec));
        goto FAIL;
    }
    u_austrcpy(cbuf, buf);
    /* Thursday, April 5, 2001 5:45:00 PM PDT 986517900000 */
    if (when == 986517900000.0) {
        log_verbose("Ok: Parsed result: %s\n", cbuf);
    } else {
        log_err("FAIL: Parsed result: %s, exp 4/5/2001 5:45 PM\n", cbuf);
    }

 FAIL:    
    udat_close(date);
    udat_close(time);
    udat_close(full);
    ucal_close(cal);

    ctest_resetTimeZone();
}

/*INTERNAL FUNCTIONS USED*/
static void VerifygetSymbols(UDateFormat* datfor, UDateFormatSymbolType type, int32_t index, const char* expected)
{
    UChar *pattern=NULL;
    UErrorCode status = U_ZERO_ERROR;
    UChar *result=NULL;
    int32_t resultlength, resultlengthout;

    
    pattern=(UChar*)malloc(sizeof(UChar) * (strlen(expected)+1));
    u_uastrcpy(pattern, expected);
    resultlength=0;
    resultlengthout=udat_getSymbols(datfor, type, index , NULL, resultlength, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR)
    {
        status=U_ZERO_ERROR;
        resultlength=resultlengthout+1;
        result=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_getSymbols(datfor, type, index, result, resultlength, &status);
        
    }
    if(U_FAILURE(status))
    {
        log_err("FAIL: Error in udat_getSymbols()... %s\n", myErrorName(status) );
        return;
    }
    if(u_strcmp(result, pattern)==0)
        log_verbose("PASS: getSymbols retrieved the right value\n");
    else{
        log_data_err("FAIL: getSymbols retrieved the wrong value\n Expected %s Got %s\n", austrdup(pattern), 
            austrdup(result) );
    }
    free(result);
    free(pattern);
}

static void VerifysetSymbols(UDateFormat* datfor, UDateFormatSymbolType type, int32_t index, const char* expected)
{
    UChar *result=NULL;
    UChar *value=NULL;
    int32_t resultlength, resultlengthout;
    UErrorCode status = U_ZERO_ERROR;

    value=(UChar*)malloc(sizeof(UChar) * (strlen(expected) + 1));
    u_uastrcpy(value, expected);
    udat_setSymbols(datfor, type, index, value, u_strlen(value), &status);
    if(U_FAILURE(status))
        {
            log_err("FAIL: Error in udat_setSymbols()  %s\n", myErrorName(status) );
            return;
        }

    resultlength=0;
    resultlengthout=udat_getSymbols(datfor, type, index, NULL, resultlength, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR){
        status=U_ZERO_ERROR;
        resultlength=resultlengthout+1;
        result=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_getSymbols(datfor, type, index, result, resultlength, &status);
    }
    if(U_FAILURE(status)){
        log_err("FAIL: error in retrieving the value using getSymbols after setting it previously\n %s\n", 
            myErrorName(status) );
        return;
    }
    
    if(u_strcmp(result, value)!=0){
        log_err("FAIL:Error in setting and then getting symbols\n Expected %s Got %s\n", austrdup(value),
            austrdup(result) );
    }
    else
        log_verbose("PASS: setSymbols successful\n");

    free(value);
    free(result);
}


static void VerifygetsetSymbols(UDateFormat* from, UDateFormat* to, UDateFormatSymbolType type, int32_t index)
{
    UChar *result=NULL;
    UChar *value=NULL;
    int32_t resultlength, resultlengthout;
    UErrorCode status = U_ZERO_ERROR;
    
    resultlength=0;
    resultlengthout=udat_getSymbols(from, type, index , NULL, resultlength, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR){
        status=U_ZERO_ERROR;
        resultlength=resultlengthout+1;
        result=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_getSymbols(from, type, index, result, resultlength, &status);
    }
    if(U_FAILURE(status)){
        log_err("FAIL: error in getSymbols() %s\n", myErrorName(status) );
        return;
    }
    
    resultlength=resultlengthout+1;
    udat_setSymbols(to, type, index, result, resultlength, &status);
    if(U_FAILURE(status))
        {
            log_err("FAIL: Error in udat_setSymbols() : %s\n", myErrorName(status) );
            return;
        }

    resultlength=0;
    resultlengthout=udat_getSymbols(to, type, index, NULL, resultlength, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR){
        status=U_ZERO_ERROR;
        resultlength=resultlengthout+1;
        value=(UChar*)malloc(sizeof(UChar) * resultlength);
        udat_getSymbols(to, type, index, value, resultlength, &status);
    }
    if(U_FAILURE(status)){
        log_err("FAIL: error in retrieving the value using getSymbols i.e roundtrip\n %s\n", 
            myErrorName(status) );
        return;
    }
    
    if(u_strcmp(result, value)!=0){
        log_data_err("FAIL:Error in setting and then getting symbols\n Expected %s Got %s\n", austrdup(result),
            austrdup(value) );
    }
    else
        log_verbose("PASS: setSymbols successful\n");

    free(value);
    free(result);
}


static UChar* myNumformat(const UNumberFormat* numfor, double d)
{
    UChar *result2=NULL;
    int32_t resultlength, resultlengthneeded;
    UErrorCode status = U_ZERO_ERROR;
    
    resultlength=0;
    resultlengthneeded=unum_formatDouble(numfor, d, NULL, resultlength, NULL, &status);
    if(status==U_BUFFER_OVERFLOW_ERROR)
    {
        status=U_ZERO_ERROR;
        resultlength=resultlengthneeded+1;
        /*result2=(UChar*)malloc(sizeof(UChar) * resultlength);*/ /* this leaks */
        result2=(UChar*)ctst_malloc(sizeof(UChar) * resultlength); /*this won't*/
        unum_formatDouble(numfor, d, result2, resultlength, NULL, &status);
    }
    if(U_FAILURE(status))
    {
        log_err("FAIL: Error in formatting using unum_format(.....) %s\n", myErrorName(status) );
        return 0;
    }
    
    return result2;
}

/**
 * The search depth for TestExtremeDates.  The total number of
 * dates that will be tested is (2^EXTREME_DATES_DEPTH) - 1.
 */
#define EXTREME_DATES_DEPTH 8

/**
 * Support for TestExtremeDates (below).
 *
 * Test a single date to see whether udat_format handles it properly.
 */
static UBool _aux1ExtremeDates(UDateFormat* fmt, UDate date,
                               UChar* buf, int32_t buflen, char* cbuf,
                               UErrorCode* ec) {
    int32_t len = udat_format(fmt, date, buf, buflen, 0, ec);
    if (!assertSuccess("udat_format", ec)) return FALSE;
    u_austrncpy(cbuf, buf, buflen);
    if (len < 4) {
        log_err("FAIL: udat_format(%g) => \"%s\"\n", date, cbuf);
    } else {
        log_verbose("udat_format(%g) => \"%s\"\n", date, cbuf);
    }
    return TRUE;
}

/**
 * Support for TestExtremeDates (below).
 *
 * Recursively test between 'small' and 'large', up to the depth
 * limit specified by EXTREME_DATES_DEPTH.
 */
static UBool _aux2ExtremeDates(UDateFormat* fmt, UDate small, UDate large,
                               UChar* buf, int32_t buflen, char* cbuf,
                               int32_t count,
                               UErrorCode* ec) {
    /* Logarithmic midpoint; see below */
    UDate mid = (UDate) exp((log(small) + log(large)) / 2);
    if (count == EXTREME_DATES_DEPTH) {
        return TRUE;
    }
    return
        _aux1ExtremeDates(fmt, mid, buf, buflen, cbuf, ec) &&
        _aux2ExtremeDates(fmt, small, mid, buf, buflen, cbuf, count+1, ec) &&
        _aux2ExtremeDates(fmt, mid, large, buf, buflen, cbuf, count+1, ec);
}

/**
 * http://www.jtcsv.com/cgibin/icu-bugs?findid=3659
 *
 * For certain large dates, udat_format crashes on MacOS.  This test
 * attempts to reproduce this problem by doing a recursive logarithmic*
 * binary search of a predefined interval (from 'small' to 'large').
 *
 * The limit of the search is given by EXTREME_DATES_DEPTH, above.
 *
 * *The search has to be logarithmic, not linear.  A linear search of the
 *  range 0..10^30, for example, will find 0.5*10^30, then 0.25*10^30 and
 *  0.75*10^30, etc.  A logarithmic search will find 10^15, then 10^7.5
 *  and 10^22.5, etc.
 */
static void TestExtremeDates() {
    UDateFormat *fmt;
    UErrorCode ec;
    UChar buf[256];
    char cbuf[256];
    const double small = 1000; /* 1 sec */
    const double large = 1e+30; /* well beyond usable UDate range */

    /* There is no need to test larger values from 1e+30 to 1e+300;
       the failures occur around 1e+27, and never above 1e+30. */
    
    ec = U_ZERO_ERROR;
    fmt = udat_open(UDAT_LONG, UDAT_LONG, "en_US",
                    0, 0, 0, 0, &ec);
    if (!assertSuccess("udat_open", &ec)) return;

    _aux2ExtremeDates(fmt, small, large, buf, LEN(buf), cbuf, 0, &ec);

    udat_close(fmt);
}

static void TestAllLocales(void) {
    int32_t idx, dateIdx, timeIdx, localeCount;
    static const UDateFormatStyle style[] = {
        UDAT_FULL, UDAT_LONG, UDAT_MEDIUM, UDAT_SHORT
    };
    localeCount = uloc_countAvailable();
    for (idx = 0; idx < localeCount; idx++) {
        for (dateIdx = 0; dateIdx < (int32_t)(sizeof(style)/sizeof(style[0])); dateIdx++) {
            for (timeIdx = 0; timeIdx < (int32_t)(sizeof(style)/sizeof(style[0])); timeIdx++) {
                UErrorCode status = U_ZERO_ERROR;
                udat_close(udat_open(style[dateIdx], style[timeIdx],
                    uloc_getAvailable(idx), NULL, 0, NULL, 0, &status));
                if (U_FAILURE(status)) {
                    log_err("FAIL: udat_open(%s) failed with (%s) dateIdx=%d, timeIdx=%d\n",
                        uloc_getAvailable(idx), u_errorName(status), dateIdx, timeIdx);
                }
            }
        }
    }
}

#endif /* #if !UCONFIG_NO_FORMATTING */
