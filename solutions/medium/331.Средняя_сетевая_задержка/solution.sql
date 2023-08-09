/*
SUM but with timestamp??
*/

SELECT SUM(1000 * EXTRACT(EPOCH FROM req2.datetime) - 1000 * EXTRACT(EPOCH FROM req1.datetime))::NUMERIC /
(SELECT count(DISTINCT request_id) FROM requests WHERE parent_request_id IS NULL)::NUMERIC
AS avg_network_time_ms
FROM requests AS req1
         INNER JOIN requests AS req2
                    ON
                            (req2.parent_request_id = req1.request_id AND
                             req1.data = req2.host AND
                             req2.type = 'RequestReceived' AND
                             req1.type = 'RequestSent') OR

                            (req1.parent_request_id = req2.request_id AND
                             req2.data LIKE CONCAT(req1.host, '%') AND
                             req2.type = 'ResponseReceived' AND
                             req1.type = 'ResponseSent'
                                )