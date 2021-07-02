switch (a.status)
{
case 0:
    strcpy(a_status, "ERROR"); // this should be a function but no time
    break;
case 1:
    strcpy(a_status, "PENDING");
    break;

case 2:
    strcpy(a_status, "ACCEPTED");
    break;
case 3:
    strcpy(a_status, "DENIED");
    break;

    program status;
case 1:
    strcpy(approval_status[2], "ACCEPTED");
    break;
case 2:
    strcpy(approval_status[2], "DENIED");
    break;
case 0:
    strcpy(approval_status[2], "");
    break;
case 3:
    strcpy(approval_status[2], ""); // let this be full
    break;