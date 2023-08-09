CREATE FUNCTION checkDot(x INTEGER, y INTEGER) RETURNS BOOLEAN AS '
    SELECT
    	x >= _X_LEFT_ AND
	x <= _X_RIGHT_ AND
	y >= _Y_BOTTOM_ AND
	y <= _Y_TOP_
' LANGUAGE SQL;


create function ori(px INTEGER, py INTEGER, qx INTEGER, qy INTEGER, rx INTEGER, ry INTEGER) returns int as '
	select (((qy - py) * (rx - qx) - (qx - px) * (ry - qy)) > 0)::INTEGER +
    2 * (((qy - py) * (rx - qx) - (qx - px) * (ry - qy)) < 0)::INTEGER;
' language SQL;

CREATE FUNCTION onSeg(px INTEGER, py INTEGER, qx INTEGER, qy INTEGER, rx INTEGER, ry INTEGER)
    RETURNS BOOLEAN AS '
	select qx <= GREATEST(px, rx) AND qx >= LEAST(px, rx) AND
        		qy <= GREATEST(py, ry) AND qy >= LEAST(py, ry);

' LANGUAGE SQL;

CREATE FUNCTION isseginseg(px0 INTEGER, py0 INTEGER, qx0 INTEGER, qy0 INTEGER, px1 INTEGER, py1 INTEGER, qx1 INTEGER, qy1 INTEGER)
    RETURNS BOOLEAN AS '
select
   	 (ori(px0, py0, qx0, qy0, px1, py1) != ori(px0, py0, qx0, qy0, qx1, qy1) AND
          		ori(px1, py1, qx1, qy1, px0, py0) != ori(px1, py1, qx1, qy1, qx0, qy0)) OR
          (onSeg(px0, py0, px1, py1, qx0, qy0) AND
          		(ori(px0, py0, qx0, qy0, px1, py1) = 0)) OR
          (onSeg(px0, py0, qx1, qy1, qx0, qy0) AND
          		ori(px0, py0, qx0, qy0, qx1, qy1) = 0) OR
          (onSeg(px1, py1, px0, py0, qx1, qy1) AND
          		ori(px1, py1, qx1, qy1, px0, py0) = 0) OR
          (onSeg(px1, py1, qx0, qy0, qx1, qy1) AND
          		ori(px1, py1, qx1, qy1, qx0, qy0) = 0);
' LANGUAGE SQL;

(SELECT dots.id FROM (SELECT points.id, points.x, points.y FROM points
                                                                    INNER JOIN objects AS obj
                                                                               ON points.id = obj.id) AS dots
 WHERE

     checkDot(dots.x, dots.y))

UNION

(SELECT l.id FROM
    (SELECT lines.id AS id,  lines.begin_x AS x0, lines.begin_y AS y0, lines.end_x AS x1, lines.end_y AS y1 FROM lines
                                                                                                                     INNER JOIN objects AS obj
                                                                                                                                ON lines.id = obj.id) AS l
 WHERE
     isseginseg(l.x0, l.y0, l.x1, l.y1, _X_LEFT_, _Y_BOTTOM_, _X_LEFT_, _Y_TOP_) or
     isseginseg(l.x0, l.y0, l.x1, l.y1, _X_RIGHT_, _Y_BOTTOM_, _X_RIGHT_, _Y_TOP_) or
     isseginseg(l.x0, l.y0, l.x1, l.y1, _X_LEFT_, _Y_BOTTOM_, _X_RIGHT_, _Y_BOTTOM_) or
     isseginseg(l.x0, l.y0, l.x1, l.y1, _X_LEFT_, _Y_TOP_, _X_RIGHT_, _Y_TOP_) OR
     checkdot(l.x0, l.y0) OR
     checkdot(l.x1, l.y1)
)

UNION

(SELECT DISTINCT poly1.id FROM
    (SELECT polygons.id, polygons.edge_order, polygons.begin_x AS x0, polygons.begin_y AS y0, polygons.end_x AS x1, polygons.end_y AS y1
     FROM polygons
              INNER JOIN objects AS obj
                         ON polygons.id = obj.id) AS poly1


        INNER JOIN
    (SELECT polygons.id, polygons.edge_order, polygons.begin_x AS x0, polygons.begin_y AS y0, polygons.end_x AS x1, polygons.end_y AS y1
     FROM polygons
              INNER JOIN objects AS obj
                         ON polygons.id = obj.id) AS poly2

    ON
                poly1.id = poly2.id AND
                poly1.edge_order = poly2.edge_order + 1 AND
                (checkdot(poly1.x0, poly1.y0) OR
                 checkdot(poly1.x1, poly1.y1) or
                 checkdot(poly2.x0, poly2.y0) or
                 checkdot(poly2.x1, poly2.y1) OR
                 isseginseg(poly1.x0, poly1.y0, poly1.x1, poly1.y1, _X_LEFT_, _Y_BOTTOM_, _X_LEFT_, _Y_TOP_) or
                 isseginseg(poly1.x0, poly1.y0, poly1.x1, poly1.y1, _X_RIGHT_, _Y_BOTTOM_, _X_RIGHT_, _Y_TOP_) or
                 isseginseg(poly1.x0, poly1.y0, poly1.x1, poly1.y1, _X_LEFT_, _Y_BOTTOM_, _X_RIGHT_, _Y_BOTTOM_) or
                 isseginseg(poly1.x0, poly1.y0, poly1.x1, poly1.y1, _X_LEFT_, _Y_TOP_, _X_RIGHT_, _Y_TOP_) or

                 isseginseg(poly2.x0, poly2.y0, poly2.x1, poly2.y1, _X_LEFT_, _Y_BOTTOM_, _X_LEFT_, _Y_TOP_) or
                 isseginseg(poly2.x0, poly2.y0, poly2.x1, poly2.y1, _X_RIGHT_, _Y_BOTTOM_, _X_RIGHT_, _Y_TOP_) or
                 isseginseg(poly2.x0, poly2.y0, poly2.x1, poly2.y1, _X_LEFT_, _Y_BOTTOM_, _X_RIGHT_, _Y_BOTTOM_) or
                 isseginseg(poly2.x0, poly2.y0, poly2.x1, poly2.y1, _X_LEFT_, _Y_TOP_, _X_RIGHT_, _Y_TOP_)
                    ))