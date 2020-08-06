#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef long double ld;

const long long INF = 1000000000000000000LL;

ll a[500010];

class DynamicConvexHull
{
private:
    struct Point
    {

        /*
         Defines the progression of the form x * param + y
         */

        long long x;
        long long y;
        bool is_query_point;
        mutable set<Point>::iterator par;
        set<Point> *master; // the set, containing this point

        Point() {}
        Point(long long x, long long y, bool is_query_point, set<Point> *master) : x(x), y(y), is_query_point(is_query_point), master(master) {}
        inline bool operator<(const Point &you) const
        {

            /*
             There are two possible situations:
             - We're adding a point to the convex hull;
             - We're looking for the optimal possible value of x * param + b for some param = x;
             
             In the first case, we will act just like we sort the points in Graham's algo.
             */

            if (!is_query_point && !you.is_query_point)
                return (x > you.x);

            /*
             In the second case, we will use the fact that first, the progressions value will decrease, and after some point will start to increase again.
             */

            if (is_query_point)
            {
                /*
                 In this case, my object is a query with param = x.
                 */
                if (you.par == master->end())
                    return false;
                if (you.par->x < you.x)
                    return ((you.y - you.par->y) <= x * (you.par->x - you.x));
                else
                    return ((you.y - you.par->y) >= x * (you.par->x - you.x));
            }
            else
            {
                /*
                 This is the previous case, vice-versa.
                 */
                if (par == master->end())
                    return true;
                if (par->x < x)
                    return (y - par->y) > you.x * (par->x - x);
                else
                    return (y - par->y) < you.x * (par->x - x);
            }
        }
    };

    typedef set<Point>::iterator position;

    set<Point> hull;

    /*
     The following routine removes the point, denoted by the iterator from the hull.
     */

    inline void remove_point(position me)
    {
        /*
         We only need to ensure that the next point has a correct predecessor pointer.
         */
        position next = me;
        ++next;
        if (next != hull.end())
            next->par = me->par;
        hull.erase(me);
    }

    inline bool is_bad_turn(position center)
    {
        position next = center, prev = center;
        ++next;
        if (center == hull.begin() || next == hull.end())
            return false;
        --prev;
        Point a = *prev, b = *center, c = *next;

        bool check_type = false;
        if (b.x < a.x)
            check_type ^= true;
        if (b.x < c.x)
            check_type ^= true;

        if (check_type)
            return (c.y - b.y) * (b.x - a.x) >= (a.y - b.y) * (b.x - c.x);
        else
            return (c.y - b.y) * (b.x - a.x) <= (a.y - b.y) * (b.x - c.x);
    }

public:
    inline void add_progression(long long x, long long y)
    {
        Point me(x, y, false, &hull);
        position pos = hull.find(me);
        if (pos != hull.end() && pos->y >= y)
            return;
        if (pos != hull.end())
            remove_point(pos);
        hull.insert(me);

        /* Recalculate the pointer to the previous point for the next point.*/

        pos = hull.find(me);
        position next = pos;
        ++next;
        if (next != hull.end())
            next->par = pos;

        /* Calculate the pointer to the previous point for the current point.*/

        if (pos != hull.begin())
        {
            position prev = pos;
            --prev;
            pos->par = prev;
        }
        else
            pos->par = hull.end();

        /*
         If the point is lying above the current hull, we can safely get rid of it.
         */

        if (is_bad_turn(pos))
        {
            remove_point(pos);
            return;
        }

        /*
         Delete the points that became unnecessary and lay after the current one.
         */

        while (next != hull.end() && is_bad_turn(next))
        {
            remove_point(next);
            next = pos;
            ++next;
        }

        /*
         Delete the points that became unnecessary and lay before the current one.
         */

        if (pos != hull.begin())
        {
            position prev = pos;
            --prev;
            while (pos != hull.begin() && is_bad_turn(prev))
            {
                remove_point(prev);
                prev = pos;
                --prev;
            }
        }
    }

    inline long long get_min_value_at(long long x)
    {
        if (hull.size() == 0)
            return INF;
        Point me(x, x, true, &hull);
        position opt = hull.lower_bound(me);
        --opt;
        return opt->x * x + opt->y;
    }
};

int main()
{
    // freopen("in.txt", "r", stdin);
    int t, i, j, n, k;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
        scanf("%lld", &a[i]);
    ll ans = LLONG_MIN, sum = 0, sum2 = 0;
    DynamicConvexHull p;
    for (i = 1; i <= n; ++i)
    {
        sum += a[i];
        sum2 += a[i] * a[i];
        ll z = sum * sum - sum2;
        ans = max(ans, z);
        ll x = p.get_min_value_at(sum);
        if (x != INF)
        {
            z = (z - x);
            ans = max(ans, z);
            // cout << i << " " << x << endl;
        }
        ll y = sum * sum + sum2;
        p.add_progression(sum + sum, -y);
    }
    printf("%lld\n", ans / 2LL);
    return 0;
}
